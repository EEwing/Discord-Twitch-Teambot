#include "Message.h"

#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using std::cerr;
using std::endl;

using namespace rapidjson;

Message Message::Parse(const Value& val) {
    Message rtn;

    if(val.HasMember("nonce") && !val["nonce"].IsNull())
        rtn.nonce = std::string(val["nonce"].GetString());
    if(val.HasMember("tts") && !val["tts"].IsNull())
        rtn.tts = val["tts"].GetBool();
    if(val.HasMember("timestamp") && !val["timestamp"].IsNull())
        rtn.timestamp = std::string(val["timestamp"].GetString());
    if(val.HasMember("mention_everyone") && !val["mention_everyone"].IsNull())
        rtn.mention_everyone = val["mention_everyone"].GetBool();
    if(val.HasMember("id") && !val["id"].IsNull())
        rtn.id = std::string(val["id"].GetString());
    //if(val.HasMember("edited_timestamp"))
        //rtn.edited_timestamp = val["edited_timestamp"].GetString();
    if(val.HasMember("content") && !val["content"].IsNull())
        rtn.content = std::string(val["content"].GetString());
    //if(val.HasMember("channel_id"))
        //rtn.channel_id = val["channel_id"].GetString();

    rtn.author = User::Parse(val["author"]);
    return rtn;
}

void Message::Print() {
    cerr << "Message: " << endl;
    cerr << "\tcontent=" << content << endl;
    cerr << "\tid=" << id << endl;
    cerr << "\ttime=" << timestamp << endl;
    cerr << "\tAuthor:" << endl;
    author.Print();
}
