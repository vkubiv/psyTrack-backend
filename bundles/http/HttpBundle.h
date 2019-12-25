#pragma once
#include "micro/ServiceBundle.h"
#include "HttpRouter.h"

struct HttpBundleConfig
{
  int port;
};

class HttpRouter;

struct HttpBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.HttpBundle";

  using Exports = sb::TypeList<HttpRouter>;
  using Externals = sb::TypeList<HttpBundleConfig>;
};