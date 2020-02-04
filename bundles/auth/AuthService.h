#pragma once
#include <future>
#include <string>
#include <vector>
#include "AuthErrors.h"

namespace auth {

class AuthBundleConfig;

class AuthService
{
public:
  
  std::future<void> init(const AuthBundleConfig& config);
  AuthErrorCode decodeJwt(const std::string& jwt, std::string* out_uid);

private:
  std::vector<std::string> pubCerts_;
  std::string jwtIssuer_;
  std::string jwtAudience_;
};

}
