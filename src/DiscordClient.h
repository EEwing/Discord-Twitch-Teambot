#ifndef DISCORD_CLIENT_H
#define DISCORD_CLIENT_H

#include <string>

//#include <curl/curl.h>
#include <vector>

#include "Message.h"

class DiscordClient {
  private:
    std::string email;
    std::string pass;

    std::string authHeader;
    std::string token;

    //CURL *curl;

    //void ApplyHeader();
    //std::string MakeRequest(const char *, std::string, std::string, bool=true);

  public:
    DiscordClient();
    ~DiscordClient();
    
    void SetEmail(std::string);
    void SetPassword(std::string);

    void Login();
    std::vector<Message> GetMessages(std::string, int=50);

    void DeleteMessage(std::string, Message);
    void DeleteMessage(std::string, std::string);

    Message SendMessage(std::string, std::string);
    
};

#endif
