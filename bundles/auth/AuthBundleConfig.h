#pragma once

namespace auth {
struct AuthBundleConfig
{
  std::string jwtPubKeyPath;
  std::string jwtIssuer;
  std::string jwtAudience;
};
}