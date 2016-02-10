#include "TwitchEndpoints.h"

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "CURLutils.h"

using namespace rapidjson;

std::string TwitchEndpoints::BASE = "https://api.twitch.tv/kraken";
std::string TwitchEndpoints::SITE = "https://api.twitch.tv/kraken";

std::string TwitchEndpoints::TEAMS;// = BASE + "/teams";
std::string TwitchEndpoints::CHANNEL;// = BASE + "/channel";
std::string TwitchEndpoints::USER;// = BASE + "/user";
std::string TwitchEndpoints::STREAMS;// = BASE + "/streams";
std::string TwitchEndpoints::SEARCH;// = BASE + "/streams";
std::string TwitchEndpoints::INGESTS;// = BASE + "/streams";

void TwitchEndpoints::Initialize() {
/*
    curl = curl_;
    CURLcode res;
    
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, BASE.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
        cerr << "Couldn't perform curl action" << endl;
            exit(EXIT_FAILURE);
    }
*/
    std::string response = GET(BASE.c_str());

    Document d;
    d.Parse(response.c_str());
        
    TEAMS = d["_links"]["teams"].GetString();
    CHANNEL = d["_links"]["channel"].GetString();
    USER = d["_links"]["user"].GetString();
    STREAMS = d["_links"]["streams"].GetString();
    SEARCH = d["_links"]["search"].GetString();
    INGESTS = d["_links"]["ingests"].GetString();

    cerr << "Teams: " << TEAMS << endl;
    cerr << "Channel: " << CHANNEL << endl;
    cerr << "User: " << USER << endl;
    cerr << "Streams: " << STREAMS << endl;
 
    //cerr << res << endl;
}

std::string TwitchEndpoints::GetTeam(std::string team) {


        //std::string response;
        std::string teamURL = TEAMS+"/"+team;
        std::string response = GET(teamURL);
        //std::string response = "";
/*
        CURLcode res;
        cerr << "Finding team at: " << teamURL << endl;
        curl_easy_setopt(curl, CURLOPT_URL, teamURL.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "Couldn't perform curl action" << endl;
                exit(EXIT_FAILURE);
        }
*/

        return response;
}
