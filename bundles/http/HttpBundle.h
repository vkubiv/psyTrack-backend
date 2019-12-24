#pragma once
#include "micro/ServiceBundle.h"

struct HttpBundleConfig
{
  int port;
};

class HttpRouter;

struct HttpBundle
{
  static constexpr auto BundleId = "com.org.xxx.DatabaseBundle";

  using Exports = sb::TypeList<Database>;
  using Externals = sb::TypeList<HttpBundleConfig>;
};