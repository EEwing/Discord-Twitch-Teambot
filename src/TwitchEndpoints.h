#ifndef TWITCH_ENDPOINTS_H
#define TWITCH_ENDPOINTS_H

#include <iostream>


using std::cerr;
using std::endl;

namespace TwitchEndpoints {

/*
    size_t response_func(void *ptr, size_t size, size_t count, void *stream) {
        ((std::string *)stream)->append((char *)ptr, 0, size*count);
        return size*count;
    }

    CURL *curl;
*/

    extern std::string BASE;// = "https://api.twitch.tv/kraken";
    extern std::string SITE;// = "https://api.twitch.tv/kraken";

    extern std::string TEAMS;// = BASE + "/teams";
    extern std::string CHANNEL;// = BASE + "/channel";
    extern std::string USER;// = BASE + "/user";
    extern std::string STREAMS;// = BASE + "/streams";
    extern std::string SEARCH;// = BASE + "/streams";
    extern std::string INGESTS;// = BASE + "/streams";

    void Initialize();

    std::string GetTeam(std::string team);
}

#endif
