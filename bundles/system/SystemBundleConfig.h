#pragma once

struct HttpConfig
{
  int port;
  int threadCount;
};

struct HttpClientConfig
{
  int maxConnectionsPerHost;
  int threadCount;
};

struct SystemBundleConfig
{
  HttpConfig http;
  HttpClientConfig httpClient;
};