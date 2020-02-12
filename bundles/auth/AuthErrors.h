#pragma once
#include <exception>

namespace auth {

enum class AuthErrorCode
{
  Ok = 0,
  JwtTokenExpired = 1,
  JwtOther,
  NotAuthorized
};

inline const char*
to_string(AuthErrorCode code)
{
  if (code == AuthErrorCode::JwtTokenExpired)
    return "jwt-token-expired";
  if (code == AuthErrorCode::JwtOther)
    return "jwt-other";
  if (code == AuthErrorCode::NotAuthorized)
    return "not-authorized";
  return "unknown";
}

class AuthException : public std::exception
{
public:
  explicit AuthException(AuthErrorCode errorCode)
    : errorCode_(errorCode)
  {}
  const char* what() const noexcept override { return to_string(errorCode_); }

  AuthErrorCode errorCode() { return errorCode_; }

private:
  AuthErrorCode errorCode_;
};

}