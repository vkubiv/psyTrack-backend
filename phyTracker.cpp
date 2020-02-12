// phyTracker.cpp : Defines the entry point for the application.
//
#include "phyTracker.h"
#include "auth/AuthBundle.h"
#include "auth/AuthBundleConfig.h"
#include "micro/Application.h"
#include "system/HttpServer.h"
#include "system/SystemBundle.h"
#include "user/UserBundle.h"
#include <iostream>

class PhyTrack : public sb::Application<PhyTrack>
{
public:
  using Bundles =
    sb::TypeList<SystemBundle, auth::AuthBundle, user::UserBundle>;

  sb::AsyncActivateResult activate(sb::BundlesLoader& loader)
  {
    auth::AuthBundleConfig authConfig = {
      "http://localhost/pubkeys",
      "https://securetoken.google.com/mindinspector-app",
      "mindinspector-app"
    };

    systemBundle_ =
      loader
        .activate<SystemBundle>(SystemBundleConfig({ { 3000, 1 }, { 8, 1 } }))
        .get();
    loader.activate<auth::AuthBundle>(authConfig).get();
    loader.activate<user::UserBundle>().get();

    return sb::make_ready_future();
  }

  void run() { systemBundle_.getService<HttpServer>()->serve(); }

private:
  sb::BundleRef<SystemBundle> systemBundle_;
};

int
main(int argc, const char** argv)
{
  std::cout << "Path: " << argv[0];

  try {

    PhyTrack app;

    auto result = app.setupBundles();

    result.get();

    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}