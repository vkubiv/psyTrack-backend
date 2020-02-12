#include "ResponseRender.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

namespace {
void
render_error(Writer<StringBuffer>& writer,
             const char* error_code,
             const char* error_message)
{
  writer.StartObject();
  writer.Key("code");
  writer.String(error_code);
  if (error_message) {
    writer.Key("message");
    writer.String(error_message);
  }
  writer.EndObject();
}
}

ResponseRender::ResponseRender(const char* error_code,
                               const char* error_message)
  : error_code_(error_code)
  , error_message_(error_message)
{}

void
ResponseRender::render(const HttpResponseWriter& response,
                       const rapidjson::Value& json)
{
  auto statusCode = Pistache::Http::Code::Ok;

  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  if (error_code_) {
    statusCode = Pistache::Http::Code::Bad_Request;
    writer.Key("error");
    render_error(writer, error_code_, error_message_);
  }

  if (!json.IsNull()) {
    writer.Key("model");
    json.Accept(writer);
  }

  writer.EndObject();

  response->send(statusCode, buffer.GetString(), MIME(Application, Json));
}
