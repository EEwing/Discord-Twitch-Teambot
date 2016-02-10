#ifndef USER_H
#define USER_H

#include <rapidjson/document.h>

using namespace rapidjson;

class User {
  public:
    std::string username;
    std::string discriminator;
    std::string id;
    std::string avatar;

    static User Parse(const Value&);

    void Print();
};

#endif
