#pragma once

#include "micro/ServiceRef.h"
#include "micro/BundleRef.h"
#include "../auth/AuthBundle.h"
#include "http/HttpRouter.h"

namespace user {
class UserController;
class UserRouter
{
public:

  using Type = sb::StatefullService;

  UserRouter(sb::ServiceRef<UserController> controller,
             sb::BundleRef<auth::AuthBundle> authBundle)
    : controller_(controller)
    , authMiddleware_(authBundle)
  {}

  void bindRoutes(HttpRouter& router);

private:
  sb::ServiceRef<UserController> controller_;
  sb::ExternServiceRef<auth::AuthMiddleware> authMiddleware_;
};
}