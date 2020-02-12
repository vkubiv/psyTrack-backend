#include "UserRouter.h"
#include "UserController.h"

void
user::UserRouter::bindRoutes(HttpRouter& router)
{
  HttpRoutes::Get(router,
                  "/users/stats",                  
                  HttpRoutes::bind(&UserController::stats, controller_.get()),
                  *authMiddleware_);
}
