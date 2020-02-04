#pragma once

#include "micro/ServiceBundle.h"

namespace user {

class UserController;
class UserService;

struct UserBundle
{
  static constexpr auto BundleId = "org.kubiv.phyTrack.UserBundle";

  using Exports = sb::TypeList<UserService>;
  using Externals = sb::TypeList<>;
};
}