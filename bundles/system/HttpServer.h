#pragma once

#include <pistache/router.h>
#include "SystemBundleConfig.h"

class HttpServer
{
public:
  Pistache::Rest::Router& rootRouter() { return router_; }
  void init(HttpConfig config) { config_ = config; }

  void serve();

private:
  Pistache::Rest::Router router_;
  HttpConfig config_;
};
