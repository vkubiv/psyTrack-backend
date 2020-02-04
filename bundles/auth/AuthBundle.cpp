#include "AuthBundle.h"
#include "AuthBundleConfig.h"
#include "AuthService.h"
#include "AuthMiddleware.h"
#include "micro/BundleActivator.h"

namespace auth {
using namespace sb;

struct AuthBundleActivator : public BundleActivator<AuthBundle>
{
  using References = TypeList<>;
  using Providers = TypeList<Provider<AuthService>, Provider<AuthMiddleware>>;

  AsyncActivateResult activate(ThisBundle<AuthBundleActivator> thisBundle)
  {
    return thisBundle.getService<AuthService>().init(
      thisBundle.getExternal<AuthBundleConfig>());
  }
};

namespace {
bool reg = ExportBundleActivator<AuthBundleActivator>();
}
}