#pragma once

struct HttpConfig
{
  int port;
  int threadCount;
};

struct SystemBundleConfig
{
  HttpConfig http;
};