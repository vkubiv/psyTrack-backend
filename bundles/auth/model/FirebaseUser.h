#pragma once

template<class Base>
class Model : public Base
{

};

namespace auth {

struct FirebaseUser
{
  static const char* table = "User";
  field<std::string> uid;

  DEF_FIELDS(uid);
  
};

}
