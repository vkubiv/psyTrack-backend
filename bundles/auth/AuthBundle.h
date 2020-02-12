#pragma once
#include "micro/ServiceBundle.h"

namespace auth {

class AuthService;
class AuthMiddleware;
class AuthBundleConfig;

struct AuthBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.AuthBundle";

  using Exports = sb::TypeList<AuthService, AuthMiddleware>;
  using Externals = sb::TypeList<AuthBundleConfig>;
  
  static bool IsRegistred;
};
}
