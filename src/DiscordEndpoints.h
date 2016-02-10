#ifndef DISCORD_ENDPOINT_H
#define DISCORD_ENDPOINT_H

#include <string.h>

namespace DiscordEndpoints {
    std::string SITE = "www.discordapp.com";

    std::string BASE = "https://discordapp.com/";
    std::string API = BASE + "api";
    std::string LOGIN = API + "/auth/login";
    std::string CHAN = API + "/channels/";
}

#endif
