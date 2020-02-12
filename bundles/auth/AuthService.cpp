#include "AuthService.h"
#include "AuthBundleConfig.h"
#include "FirebaseCertService.h"
#include "jwt/json/json.hpp"
#include "jwt/jwt.hpp"
#include <fstream>
#include <iostream>
namespace auth {

void
AuthService::init(const AuthBundleConfig& config)
{
  using json = nlohmann::json;

  jwtIssuer_ = config.jwtIssuer;
  jwtAudience_ = config.jwtAudience;
}

AuthAsyncResult<std::string>
AuthService::decodeAuthHeader(const std::string& authHeader)
{
  auto bearerPrefix = "Bearer ";
  if (authHeader.find(bearerPrefix) != 0) {

    return makeAsyncResultError<std::string>(AuthErrorCode::JwtOther);
  }

  auto jwtToken = authHeader.substr(strlen(bearerPrefix));

  using namespace jwt::params;

  std::string keyId;
  {
    std::error_code ec;
    auto decObj =
      jwt::decode(jwtToken, algorithms({ "rs256" }), ec, verify(false));
    keyId = decObj.header().create_json_obj()["kid"];
  }

  return firebaseCertService_->fetchCert(keyId).then(
    [this, jwtToken = std::move(jwtToken)](const std::string& key) {
      std::error_code ec;

      auto decObj = jwt::decode(jwtToken,
                                algorithms({ "rs256" }),
                                ec,
                                issuer(jwtIssuer_),
                                aud(jwtAudience_),
                                validate_iat(true),
                                secret(key));

      if (ec) {

        std::cout << std::endl << key << std::endl;
        std::cout << jwtToken << std::endl;

        if (ec == jwt::VerificationErrc::TokenExpired)
          return AuthResult<std::string>(AuthErrorCode::JwtTokenExpired);

        return AuthResult<std::string>(AuthErrorCode::JwtOther);
      }

      return AuthResult<std::string>(
        decObj.payload().get_claim_value<std::string>("user_id"));
    },
    Async::Throw);
}
}