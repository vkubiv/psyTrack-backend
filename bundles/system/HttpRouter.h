#pragma once

#include "Middleware.h"
#include <pistache/router.h>

using HttpRouter = Pistache::Rest::Router;
using HttpRouteResult = Pistache::Rest::Route::Result;

namespace HttpRoutes {

namespace Private {
template<class Context, class Middleware, class... Middlewares>
std::function<void(Context context,
                   const HttpRequest& request,
                   HttpResponseWriter response)>
BindMiddlewaresImpl(Middleware& middleware, Middlewares&... middlewares)
{

  auto callNextMiddleware = BindMiddlewaresImpl(middlewares...);

  return [&middleware, callNextMiddleware](Context context,
                                           const HttpRequest& request,
                                           HttpResponseWriter response) {
    middleware.handle(
      *context,
      request,
      std::move(response),
      [callNextMiddleware, context](const HttpRequest& request,
                                    HttpResponseWriter response) {
        callNextMiddleware(context, request, std::move(response));
      });
  };
}

template<class Context, class Handler>
std::function<void(Context context,
                   const HttpRequest& request,
                   HttpResponseWriter response)>
BindMiddlewaresImpl(Handler& handler)
{
  return handler;
}

template<class... Middlewares>
std::function<HttpRouteResult (const HttpRequest& request,
                                            HttpResponseWriter response)>
ApplyMiddlewares(Middlewares&... middleware);

template<class... Middlewares, class Handler>
std::function<HttpRouteResult(const HttpRequest& request,
                              HttpResponseWriter response)>
ApplyMiddlewares(Middlewares&... middleware, Handler & handler)
{
  using Context = AggregatedContext<Middlewares...>;

  auto binded = BindMiddlewaresImpl<Context>(middleware..., handler);

  return [binded](const HttpRequest& request, HttpResponseWriter response) {
    auto context = std::make_shared<typename Context::element_type>();
    binded(context, request, std::move(response));
    return HttpRouteResult::Ok;
  };
}
}

template<class... Middlewares>
void
Get(HttpRouter& router, const std::string& resource, Middlewares... middlewares)
{
  using namespace Pistache::Rest;
  Routes::Get(router, resource, Private::ApplyMiddlewares(middlewares...));
}

template<class... Middlewares>
void
Post(HttpRouter& router,
     const std::string& resource,
     Middlewares... middlewares)
{
  using namespace Pistache::Rest;
  Routes::Post(router, resource, Private::ApplyMiddlewares(middlewares...));
}

template<typename Context, typename Cls, typename Obj>
std::function<void(Context context,
                   const HttpRequest& request,
                   HttpResponseWriter response)>
bind(void (Cls::*func)(Context context, const HttpRequest&, HttpResponseWriter),
     Obj obj)
{

  return [=](Context context, const HttpRequest& request,
             HttpResponseWriter response) {
    (obj->*func)(context, request, std::move(response));
  };
}

}