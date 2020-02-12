#pragma once
#include "micro/ServiceBundle.h"
#include "SystemBundleConfig.h"

class HttpServer;
class HttpClient;

struct SystemBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.SystemBundle";

  using Exports = sb::TypeList<HttpServer, HttpClient>;
  using Externals = sb::TypeList<SystemBundleConfig>;

  static bool IsRegistred;
};