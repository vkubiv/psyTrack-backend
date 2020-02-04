#pragma once

#include "../system/Http.h"
#include "../system/Middleware.h"
#include "micro/ServiceRef.h"
#include <string>

namespace auth {

class AuthService;

class AuthMiddleware
{
public:
  struct Context
  {
    std::string userId;
  };

  AuthMiddleware(sb::ServiceRef <AuthService> authService)
    : authService_(authService)
  {}

  void handle(Context& context,
              const HttpRequest& request,
              HttpResponseWriter response,
              NextMiddleware next);

private:
  sb::ServiceRef<AuthService> authService_;
};
}
