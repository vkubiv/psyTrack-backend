#include "AuthMiddleware.h"
#include "AuthService.h"

using namespace Pistache;

void
auth::AuthMiddleware::handle(Context& context,
                             const HttpRequest& request,
                             HttpResponseWriter response,
                             NextMiddleware next)
{
  auto headers = request.headers();
  auto authorization = headers.get<Http::Header::Authorization>();
  auto bearerPrefix = "Bearer ";
  if (authorization->value().find(bearerPrefix) != 0) {
    auto token = authorization->value().substr(strlen(bearerPrefix));

    auto ec = authService_->decodeJwt(token, &context.userId);

  }
}
