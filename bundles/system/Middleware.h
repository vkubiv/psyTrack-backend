#pragma once
#include "Http.h"
#include <functional>
#include <memory>
#include <functional>

template<class... Middlewares>
struct AggregatedContextType : public Middlewares::Context...
{};

template<class... Middlewares>
using AggregatedContext =
  std::shared_ptr<AggregatedContextType<Middlewares...>>;

using NextMiddleware =
  std::function<void(const HttpRequest& request, HttpResponseWriter response)>;
