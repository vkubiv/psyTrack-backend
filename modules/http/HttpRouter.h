#pragma once

#include "Middleware.h"
#include <pistache/router.h>

using HttpRouter = Pistache::Rest::Router;
using HttpRouteResult = Pistache::Rest::Route::Result;

namespace HttpRoutes {

namespace Private {

template<class Context, class Handler, class... Middlewares>
class HandlerWithBindedMiddlewares;

template<class Context, class Handler>
class HandlerWithBindedMiddlewares<Context, Handler>
{
public:
  HandlerWithBindedMiddlewares(const Handler& handler)
    : handler_(handler){};

  void handle(Context context,
              const HttpRequest& request,
              HttpResponseWriter response) const
  {
    handler_(context, request, std::move(response));
  }

private:
  Handler handler_;
};

template<class Context, class Handler, class Middleware, class... Middlewares>
class HandlerWithBindedMiddlewares<Context, Handler, Middleware, Middlewares...>
  : public HandlerWithBindedMiddlewares<Context, Handler, Middlewares...>
{
  using base = HandlerWithBindedMiddlewares<Context, Handler, Middlewares...>;

public:
  HandlerWithBindedMiddlewares(const Handler& handler,
                               Middleware& middleware,
                               Middlewares&... middlewares)
    : base(handler, middlewares...)
    , middleware_(middleware)
  {}

  void handle(Context context,
              const HttpRequest& request,
              HttpResponseWriter response) const
  {
    middleware_.handle(
      *context,
      request,
      std::move(response),
      [context, this](const HttpRequest& request, HttpResponseWriter response) {
        base::handle(context, request, std::move(response));
      });
  }

private:
  Middleware& middleware_;
};

template<class Handler, class... Middlewares>
std::function<HttpRouteResult(const HttpRequest& request,
                              Pistache::Http::ResponseWriter response)>
ApplyMiddlewares(const Handler& handler, Middlewares&... middleware)
{
  using Context = AggregatedContext<Middlewares...>;

  HandlerWithBindedMiddlewares<Context, Handler, Middlewares...> binded(
    handler, middleware...);

  return [binded = std::move(binded)](const HttpRequest& request,
                                      Pistache::Http::ResponseWriter response) {
    auto context = std::make_shared<typename Context::element_type>();
    binded.handle(context,
                  request,
                  std::make_shared<Pistache::Http::ResponseWriter>(
                    std::move(response)));
    return HttpRouteResult::Ok;
  };
}
}

template<class... Middlewares, class Handler>
void
Get(HttpRouter& router,
    const std::string& resource,
    const Handler& hander,
    Middlewares&... middlewares)
{
  using namespace Pistache::Rest;
  Routes::Get(
    router, resource, Private::ApplyMiddlewares(hander, middlewares...));
}

template<class... Middlewares, class Handler>
void
Post(HttpRouter& router,
     const std::string& resource,
     const Handler& hander,
     Middlewares&... middlewares)
{
  using namespace Pistache::Rest;
  Routes::Post(
    router, resource, Private::ApplyMiddlewares(hander, middlewares...));
}

template<typename Context, typename Cls, typename Obj>
std::function<void(Context context,
                   const HttpRequest& request,
                   HttpResponseWriter response)>
bind(void (Cls::*func)(Context context, const HttpRequest&, HttpResponseWriter),
     Obj obj)
{

  return [=](Context context,
             const HttpRequest& request,
             HttpResponseWriter response) {
    (obj->*func)(context, request, std::move(response));
  };
}

}