#pragma once
#include "AuthErrors.h"
#include "micro/ServiceRef.h"
#include "AuthAsyncResult.h"
#include <future>
#include <map>
#include <string>

namespace auth {

class AuthBundleConfig;
class FirebaseCertService;

class AuthService
{
public:
  AuthService(sb::ServiceRef<FirebaseCertService> firebaseCertService)
    : firebaseCertService_(firebaseCertService)
  {}

  void init(const AuthBundleConfig& config);
  AuthAsyncResult<std::string> decodeAuthHeader(
    const std::string& authHeader);

private:
  std::map<std::string, std::string> pubCerts_;
  std::string jwtIssuer_;
  std::string jwtAudience_;

  sb::ServiceRef<FirebaseCertService> firebaseCertService_;
};

}
