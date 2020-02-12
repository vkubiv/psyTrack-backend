#include "UserController.h"
#include "response-render/ResponseRender.h"

void
user::UserController::stats(Context context,
                            const HttpRequest& request,
                            HttpResponseWriter response)
{
  ResponseRender().render(response);
}
