#include "AuthService.h"
#include "AuthBundleConfig.h"
#include "jwt/json/json.hpp"
#include "jwt/jwt.hpp"
#include <fstream>
namespace auth {

std::future<void>
AuthService::init(const AuthBundleConfig& config)
{
  using json = nlohmann::json;

  // config.jwtPubKeyPath
  return std::async([this, &config]() {
    std::fstream fin(config.jwtPubKeyPath);
    std::stringstream buffer;
    buffer << fin.rdbuf();

    auto certs = json::parse(buffer.str());

    for (auto cert : certs.items()) {
      pubCerts_.push_back(cert.value());
    }
  });
}

AuthErrorCode
AuthService::decodeJwt(const std::string& jwt, std::string* outUserId)
{
  using namespace jwt::params;

  for (const auto& cert : pubCerts_) {

    std::error_code ec;

    auto decObj = jwt::decode(jwt,
                              algorithms({ "rs256" }),
                              ec,
                              issuer(jwtIssuer_),
                              aud(jwtAudience_),
                              validate_iat(true),
                              secret(cert));

    if (ec.value() !=
        static_cast<int>(jwt::VerificationErrc::InvalidSignature)) {
      if (ec) {
        if (ec.value() == static_cast<int>(jwt::VerificationErrc::TokenExpired))
          return AuthErrorCode::JwtTokenExpired;
        return AuthErrorCode::JwtOther;
      }

      *outUserId = decObj.payload().get_claim_value<std::string>("user_id");

      return AuthErrorCode::Ok;
    }
  }

  return AuthErrorCode::JwtOther;
}
}