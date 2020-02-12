
#include "http/Http.h"
#include "rapidjson/document.h"

class ResponseRender
{
public:
  ResponseRender(const char* error_code = nullptr,
                 const char* error_message = nullptr);

  void render(const HttpResponseWriter& writer,
              const rapidjson::Value& json = rapidjson::Value());

private:
  const char* error_code_;
  const char* error_message_;
};