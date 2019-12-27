#include "HttpServer.h"
#include <pistache/endpoint.h>

using namespace Pistache;

void HttpServer::serve()
{
  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(config_.port));
  auto opts = Pistache::Http::Endpoint::options().threads(config_.threadCount);

  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router_.handler());
  server.serve();
}