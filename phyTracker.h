// phyTracker.h : Include file for standard system include files,
// or project specific include files.

#pragma once

/*

#include "jwt/jwt.hpp"
#include <cpr/cpr.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;
using namespace Rest;

int
main()
{
  Router router;

  Routes::Get(router,
              "/users/:id",
              [](const Rest::Request& request, Http::ResponseWriter response) {
                auto id = request.param(":id").as<int>();

                response.send(Pistache::Http::Code::Ok,
                              "Hello World " + std::to_string(id) + "\n");
                return Route::Result::Ok;
              });

  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(3000));
  auto opts = Pistache::Http::Endpoint::options().threads(1);

  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router.handler());
  server.serve();
}*/