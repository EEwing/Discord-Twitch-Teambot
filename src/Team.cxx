#include "Team.h"

#include <iostream>
#include <string>

#include <tidy.h>
#include <tidybuffio.h>

#include <tinyxml2.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "CURLutils.h"
#include "TwitchEndpoints.h"

using namespace tinyxml2;
using namespace rapidjson;

using std::cerr;
using std::endl;

std::string ReadPage(std::string url) {
    std::string response = GET(url);

    TidyDoc doc = tidyCreate();
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int rc = -1;
    bool ok = tidyOptSetBool(doc, TidyXhtmlOut, yes);
    if ( ok )
        rc = tidySetErrorBuffer( doc, &errbuf );    // Capture diagnostics
    if ( rc >= 0 )
        rc = tidyParseString( doc, response.c_str() );         // Parse the input
    if ( rc >= 0 )
        rc = tidyCleanAndRepair( doc );             // Tidy it up!
    if ( rc >= 0 )
        rc = tidyRunDiagnostics( doc );             // Kvetch
    if ( rc > 1 )                                    // If error, force output.
        rc = ( tidyOptSetBool(doc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
        rc = tidySaveBuffer( doc, &output );        // Pretty Print
    if ( rc < 0 )
        cerr << "A severe error " << rc << " has occured." << endl;
    return std::string((char *)output.bp);
}

Team::Team(std::string url_) {
    url = url_;
}

std::vector<Stream> Team::GetUsers(bool deep) {
    std::string memberListBase = url + "/live_member_list?page=";
    bool readingMembers = true;
    int numPages = 0;

    std::vector<Stream> members;

    while(readingMembers) {
        std::string pageURL = memberListBase + std::to_string(numPages+1);
        numPages++;

        std::string html = ReadPage(pageURL);

        XMLDocument doc;
        doc.Parse( html.c_str() );

        XMLElement *root = doc.RootElement();
        root = root->FirstChildElement("body"); // Get Body
        root = root->FirstChildElement("div"); // Get Member List Div
        XMLElement *usrElement = root->FirstChildElement("div");
        int numLiveMembers = 0;
        int numOfflineMembers = 0;
        while(usrElement != NULL) {
            if(usrElement->Attribute("class", "member live")) {
                Stream stream;

                std::string streamer = usrElement->FirstChildElement("a")->FirstChildElement("span")->GetText();

                Document d;
                d.Parse(GET((TwitchEndpoints::STREAMS + "/" + streamer).c_str()).c_str());

                if(d.HasMember("stream") && !d["stream"].IsNull()) {
                    Value &v = d["stream"];

                    if(v.HasMember("game") && !v["game"].IsNull())
                        stream.game = v["game"].GetString();

                    if(v.HasMember("viewers") && !v["viewers"].IsNull())
                        stream.viewers = v["viewers"].GetInt();

                    Value &chan = v["channel"];

                    if(chan.HasMember("status") && !chan["status"].IsNull())
                        stream.title = chan["status"].GetString();

                    if(chan.HasMember("url") && !chan["url"].IsNull())
                        stream.url = chan["url"].GetString();

                    if(chan.HasMember("name") && !chan["name"].IsNull())
                        stream.name = chan["name"].GetString();

                    if(chan.HasMember("followers") && !chan["followers"].IsNull())
                        stream.followers = chan["followers"].GetInt();
                
		    //stream.viewerCount = atoi(usrElement->FirstChildElement("span")->GetText());
                    //stream.url = TwitchEndpoints::SITE + usrElement->FirstChildElement("a")->Attribute("href");

                

                    members.push_back(stream);

                    ++numLiveMembers;
                }
            }
            if(usrElement->Attribute("class", "member")) {
                
                ++numOfflineMembers;
            }
            usrElement = usrElement->NextSiblingElement("div");
        }
        if(numLiveMembers+numOfflineMembers == 0 || (!deep && numLiveMembers == 0))
            readingMembers = false;
    }
    return members;
}
