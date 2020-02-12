#include "micro/BundleRef.h"
#include "http/Async.h"
#include "system/HttpClient.h"
#include "system/SystemBundle.h"

namespace auth {
class FirebaseCertService
{
public:
  FirebaseCertService(sb::BundleRef<SystemBundle> systemBundle)
    : httpClient_(systemBundle)
  {}

  void init(const std::string& jwtPubKeyUrl) { jwtPubKeyUrl_ = jwtPubKeyUrl; }

  Async::Promise<std::string> fetchCert(const std::string& keyId);

private:
  sb::ExternServiceRef<HttpClient> httpClient_;
  std::string jwtPubKeyUrl_;
};

}