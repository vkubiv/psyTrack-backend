#pragma once
#include "micro/ServiceBundle.h"

struct AuthBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.AuthBundle";

  using Exports = sb::TypeList<HttpServer>;
  using Externals = sb::TypeList<SystemBundleConfig>;
};
