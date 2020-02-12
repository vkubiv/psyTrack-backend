#include "FirebaseCertService.h"
#include "jwt/algorithm.hpp"
#include "rapidjson/document.h"
#include <openssl/bio.h>

using namespace jwt;

namespace auth {
namespace {

inline void
x509_deletor(X509* ptr)
{
  if (ptr)
    X509_free(ptr);
}

using x509_deletor_t = decltype(&x509_deletor);
using EC_X509_uptr = std::unique_ptr<X509, x509_deletor_t>;

}

Async::Promise<std::string>
auth::FirebaseCertService::fetchCert(const std::string& keyId)
{
  return httpClient_->get(jwtPubKeyUrl_)
    .send()
    .then(
      [keyId](const Http::Response& response) {
        rapidjson::Document document;
        document.Parse(response.body().data(), response.body().length());
        auto & cert = document[keyId];

        BIO_uptr bufX509key{ BIO_new_mem_buf((void*)cert.GetString(),
                                             cert.GetStringLength()),
                             bio_deletor };

        if (!bufX509key) {
          throw MemoryAllocationException("BIO_new_mem_buf failed");
        }

        EC_X509_uptr x509key{ PEM_read_bio_X509(
                                bufX509key.get(), nullptr, nullptr, nullptr),
                              x509_deletor };

        EC_PKEY_uptr pubKey{ X509_get_pubkey(x509key.get()), ev_pkey_deletor };

        BIO_uptr bufPubKey{ BIO_new(BIO_s_mem()), bio_deletor };

        PEM_write_bio_PUBKEY(bufPubKey.get(), pubKey.get());

        char* pubKeyData = 0;

        auto publicKeySize =
          (size_t)BIO_get_mem_data(bufPubKey.get(), &pubKeyData);

        return std::string(pubKeyData, publicKeySize);
      },
      Async::Throw);
}
}