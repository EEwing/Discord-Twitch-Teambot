#include "User.h"

#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using std::cerr;
using std::endl;

using namespace rapidjson;

User User::Parse(const Value& val) {
    User rtn;

    if(val.HasMember("username") && !val["username"].IsNull())
        rtn.username = val["username"].GetString();
    if(val.HasMember("discriminator") && !val["discriminator"].IsNull())
        rtn.discriminator = val["discriminator"].GetString();
    if(val.HasMember("id") && !val["id"].IsNull())
        rtn.id = val["id"].GetString();
    if(val.HasMember("avatar") && !val["avatar"].IsNull())
        rtn.avatar = val["avatar"].GetString();

    return rtn;
}

void User::Print() {
    cerr << "User: " << username << endl;
    cerr << "\tid=" << id << endl;
}
