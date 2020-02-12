#include "AuthBundle.h"
#include "AuthBundleConfig.h"
#include "AuthMiddleware.h"
#include "AuthService.h"
#include "FirebaseCertService.h"
#include "system/SystemBundle.h"
#include "micro/BundleActivator.h"

namespace auth {
using namespace sb;

struct AuthBundleActivator : public BundleActivator<AuthBundle>
{
  using References = TypeList<SystemBundle>;
  using Providers = TypeList<Provider<AuthService>,
                             Provider<AuthMiddleware>,
                             Provider<FirebaseCertService>>;

  AsyncActivateResult activate(ThisBundle<AuthBundleActivator> thisBundle)
  {
    auto authConfig = thisBundle.getExternal<AuthBundleConfig>();
    thisBundle.getService<FirebaseCertService>().init(authConfig.jwtPubKeyPath);

    thisBundle.getService<AuthService>().init(authConfig);
    return make_ready_future();
  }
};

bool AuthBundle::IsRegistred = ExportBundleActivator<AuthBundleActivator>();

}