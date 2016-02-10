#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

#include "User.h"

#include <rapidjson/document.h>

using namespace rapidjson;

class Message {
  public:
    std::string nonce;
    std::string timestamp;
    std::string id;
    std::string edited_timestamp;
    std::string content;
    std::string channel_id;

    bool        tts;
    bool        mention_everyone;

    User author;

    //std::string attachments;
    //std::string embeds;
    //std::string mentions;

    static Message Parse(const Value&);
    void Print();
};

#endif
