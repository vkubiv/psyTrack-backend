#pragma once
#include "micro/ServiceBundle.h"
#include "SystemBundleConfig.h"

class HttpServer;

struct SystemBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.SystemBundle";

  using Exports = sb::TypeList<HttpServer>;
  using Externals = sb::TypeList<SystemBundleConfig>;
};