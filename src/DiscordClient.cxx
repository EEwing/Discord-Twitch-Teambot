#include "DiscordClient.h"

#include <string>
#include <unistd.h>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/error/en.h>

#include "DiscordEndpoints.h"
#include "Message.h"
#include "TwitchEndpoints.h"
#include "CURLutils.h"

using namespace rapidjson;

using std::cerr;
using std::endl;

DiscordClient::DiscordClient() {
    //Document d;
    //d.Parse(TwitchEndpoints::GetTeam("theanimeclub").c_str());
}

DiscordClient::~DiscordClient() {
    //if(curl)
        //curl_easy_cleanup(curl);
    //curl_global_cleanup();
}

void DiscordClient::Login() {
    std::string postfield = "email=" + email + "&password=" + pass;
    std::string response = POST(DiscordEndpoints::LOGIN.c_str(), postfield);
    //std::string response = MakeRequest("post", DiscordEndpoints::LOGIN.c_str(), postfield, false);

    Document d;
    d.Parse(response.c_str());

    if(!d.HasMember("token")) {
        if(d.HasMember("email")) {
            cerr << d["email"][0].GetString() << endl;
            exit(EXIT_FAILURE);
        } else if(d.HasMember("password")) {
            cerr << d["password"][0].GetString() << endl;
            exit(EXIT_FAILURE);
        } else {
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);
            cerr << "Could not connect!" << endl;
            cerr << "Object: " << endl << buffer.GetString() << endl;
            exit(EXIT_FAILURE);
        }
    }
    Value &val = d["token"];
    assert(val.IsString());
    token = val.GetString();

    authHeader = "authorization: " + token;
}

void DiscordClient::SetEmail(std::string email) {
    this->email = email;
}

void DiscordClient::SetPassword(std::string pass) {
    this->pass = pass;
}

std::vector<Message> DiscordClient::GetMessages(std::string channel, int numMessages) {
    std::vector<Message> messages;
    std::string chan = DiscordEndpoints::CHAN + channel + "/messages";

    //std::string response = MakeRequest("get", chan, "");
    std::string response = GET(chan, authHeader);

    Document d;
    d.Parse(response.c_str());

    if(d.IsArray()) {
        for(SizeType i=0; i<d.Size(); ++i) {
            messages.push_back(Message::Parse(d[i]));
        }
    }

    return messages;
}

void DiscordClient::DeleteMessage(std::string channel, Message msg) {
    DeleteMessage(channel, msg.id);
}

void DiscordClient::DeleteMessage(std::string channel, std::string msg_id) {
    std::string msg_formatted = DiscordEndpoints::CHAN + channel + "/messages/" + msg_id;
    std::string response = CUSTOM(msg_formatted, "DELETE", authHeader);
}

Message DiscordClient::SendMessage(std::string channel, std::string msg) {
    std::string msg_formatted = DiscordEndpoints::CHAN + channel + "/messages";
    Document doc;
    doc.SetObject();

    Value key("content", doc.GetAllocator());
    Value val(msg.c_str(), doc.GetAllocator());
    doc.AddMember(key, val, doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    //cerr << "Posting message: " << buffer.GetString() << " ... ";

    std::string response = POST(msg_formatted, buffer.GetString(), authHeader);

    //cerr << "done. " << endl;


    Document d;
    ParseResult ok = d.Parse(response.c_str());

    if(!ok) {
        cerr << "JSON parse error!" << GetParseError_En(ok.Code()) << endl;
        cerr  << response << endl;
        return SendMessage(channel, msg);
    }

    if(d.HasMember("retry_after") && !d["retry_after"].IsNull()) {
        int sec = (d["retry_after"].GetInt()/1000) +1;
        cerr << "Rate limited: Retrying in " << sec << " seconds" << endl;
        sleep(sec);
        return SendMessage(channel, msg);
    }

    return Message::Parse(d);
}

