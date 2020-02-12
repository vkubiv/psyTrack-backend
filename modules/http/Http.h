#pragma once

#include <pistache/router.h>
#include <memory>

using HttpRequest = Pistache::Rest::Request;
using HttpResponseWriter = std::shared_ptr<Pistache::Http::ResponseWriter>;