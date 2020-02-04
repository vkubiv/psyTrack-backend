#pragma once

#include "micro/ServiceRef.h"
#include "micro/BundleRef.h"
#include "../auth/AuthBundle.h"
#include "../system/HttpRouter.h"

namespace user {
class UserController;
class UserRouter
{
public:
  UserRouter(sb::ServiceRef<UserController> controller,
             sb::BundleRef<auth::AuthBundle> authBundle)
    : controller_(controller)
  {}

  void bindRoutes(HttpRouter& router);

private:
  sb::ServiceRef<UserController> controller_;
  sb::ServiceRef<auth::AuthMiddleware> authMiddleware_;
};
}