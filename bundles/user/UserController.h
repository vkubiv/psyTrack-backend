#pragma once

#include "http/Http.h"
#include "bundles/auth/AuthMiddleware.h"

namespace user {
class UserController
{
public:
  using Context = AggregatedContext<auth::AuthMiddleware>;

  void stats(Context context, const HttpRequest& request,
             HttpResponseWriter response);
};

}