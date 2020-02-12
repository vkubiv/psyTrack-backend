#include "UserBundle.h"
#include "UserController.h"
#include "UserRouter.h"
#include "UserService.h"
#include "auth/AuthBundle.h"
#include "micro/BundleActivator.h"
#include "system/HttpServer.h"
#include "system/SystemBundle.h"

using namespace sb;

namespace user {

struct UserBundleActivator : public BundleActivator<UserBundle>
{
  using References = TypeList<SystemBundle, auth::AuthBundle>;
  using Providers = TypeList<Provider<UserController>,
                             Provider<UserService>,
                             Provider<UserRouter>>;

  AsyncActivateResult activate(ThisBundle<UserBundleActivator> thisBundle)
  {
    auto httpServer =
      thisBundle.onActive<SystemBundle>().get().getService<HttpServer>();   

    thisBundle.getService<UserRouter>().bindRoutes(httpServer->rootRouter()); 

    return make_ready_future();
  }
};

bool UserBundle::IsRegistred = ExportBundleActivator<UserBundleActivator>();

}
