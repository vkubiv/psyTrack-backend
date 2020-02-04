#include <system_error>

namespace auth {

enum class AuthErrorCode
{
  Ok = 0,
  JwtTokenExpired = 1,
  JwtOther
};

const char*
to_string(AuthErrorCode code)
{
  if (code == AuthErrorCode::JwtTokenExpired)
    return "jwt-token-expired";
  if (code == AuthErrorCode::JwtOther)
    return "jwt-other";
  return "unknown";
}

}