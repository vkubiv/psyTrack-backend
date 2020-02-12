#include "SystemBundle.h"
#include "HttpClient.h"
#include "HttpServer.h"
#include "micro/BundleActivator.h"

using namespace sb;

struct SystemBundleActivator : public BundleActivator<SystemBundle>
{
  using References = TypeList<>;
  using Providers = TypeList<Provider<HttpServer>, Provider<HttpClient>>;

  AsyncActivateResult activate(ThisBundle<SystemBundleActivator> thisBundle)
  {
    const auto& config = thisBundle.getExternal<SystemBundleConfig>();

    thisBundle.getService<HttpServer>().init(config.http);
    thisBundle.getService<HttpClient>().init(config.httpClient);
    return make_ready_future();
  }
};

bool SystemBundle::IsRegistred = ExportBundleActivator<SystemBundleActivator>();
