#include "AuthMiddleware.h"
#include "AuthService.h"
#include "response-render/ResponseRender.h"

using namespace Pistache;

void
auth::AuthMiddleware::handle(Context& context,
                             const HttpRequest& request,
                             HttpResponseWriter response,
                             NextMiddleware next)
{
  try {
    auto headers = request.headers();
    auto authHeader = headers.tryGet<Http::Header::Authorization>();
    if (!authHeader) {
      ResponseRender(to_string(auth::AuthErrorCode::NotAuthorized))
        .render(response);
      return;
    }

    authService_->decodeAuthHeader(authHeader->value())
      .then(
        [&, next, response](const AuthResult<std::string>& result) mutable {
          if (result.errorCode == AuthErrorCode::Ok) {
            context.userId = result.value;
            next(request, response);
            return;
          }

          ResponseRender(to_string(result.errorCode)).render(response);
        },
        [response](std::exception_ptr exPtr) {
          try {
            std::rethrow_exception(exPtr);            
          } catch (std::exception& e) {
            ResponseRender("exception", e.what()).render(response);
          }
        });
  } catch (std::exception& e) {
    ResponseRender("exception", e.what()).render(response);
  }
}
