#pragma once


struct AuthBundleConfig
{
  std::string jwtPubKey;
  std::string jwtIssuer;
  std::string jwtAudience;
};