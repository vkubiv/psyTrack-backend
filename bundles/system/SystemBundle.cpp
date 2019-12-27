#include "SystemBundle.h"
#include "micro/BundleActivator.h"
#include "HttpServer.h"

using namespace sb;

struct SystemBundleActivator : public BundleActivator<SystemBundle>
{
  using References = TypeList<>;
  using Providers = TypeList<Provider<HttpServer>>;

  AsyncActivateResult activate(ThisBundle<SystemBundleActivator> thisBundle)
  {
    return make_ready_future();
  }
};

namespace {
bool reg = ExportBundleActivator<SystemBundleActivator>();
}
