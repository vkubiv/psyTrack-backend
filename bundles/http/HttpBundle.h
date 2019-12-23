#pragma once

struct HttpBundleConfig
{};

struct HttpBundle
{
  static constexpr auto BundleId = "com.org.xxx.DatabaseBundle";

  using Exports = sb::TypeList<Database>;
  using Externals = sb::TypeList<HttpBundleConfig>;
};