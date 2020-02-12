
#include "SystemBundleConfig.h"
#include <pistache/client.h>

using namespace Pistache;

class HttpClient
{
public:
  void init(HttpClientConfig config)
  {
    auto opts = Http::Client::options()
                  .threads(config.threadCount)
                  .maxConnectionsPerHost(config.maxConnectionsPerHost);
    client_.init(opts);
  }

  Http::RequestBuilder get(const std::string& resource)
  {
    return client_.get(resource);
  }

  ~HttpClient() { client_.shutdown(); }

private:
  Http::Client client_;
};