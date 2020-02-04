
class ResponseRender
{
public:
  ResponseRender(char* error_code, char* error_message);

private:
  char* error_code_;
  char* error_message_;
};