#include "UserBundle.h"
#include "UserController.h"
#include "UserService.h"
#include "micro/BundleActivator.h"

using namespace sb;

namespace user {

struct UserBundleActivator : public BundleActivator<UserBundle>
{
  using References = TypeList<>;
  using Providers =
    TypeList<Provider<UserController>, Provider<UserService>>;

  AsyncActivateResult activate(ThisBundle<UserBundleActivator> thisBundle)
  {
    return make_ready_future();
  }
};

namespace {
bool reg = ExportBundleActivator<UserBundleActivator>();
}
}