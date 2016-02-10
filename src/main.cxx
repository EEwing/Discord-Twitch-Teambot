#include <iostream>

#include <string>
#include <unistd.h>
#include <vector>

#include "CURLutils.h"
#include "DiscordClient.h"
#include "Message.h"
#include "Team.h"
#include "TwitchEndpoints.h"

using std::cerr;
using std::cout;
using std::cin;
using std::endl; 

std::string channel = "141081037932462080";

long delay=60*5;

int main(int argc, char **argv) {

    Init_CURL();
    TwitchEndpoints::Initialize();

    std::string email;
    std::string pass;

    cout << "Email: ";
    cin >> email;
    pass = std::string(getpass("Password: "));


    DiscordClient client;
    client.SetEmail(email);
    client.SetPassword(pass);

    client.Login();
    
    Team animeclub("http://www.twitch.tv/team/theanimeclub");

// !addteam theanimeclub
// !adduser Quentillionaire

    while(1) {
        // Remove previous messages
        std::vector<Message> messages;
        messages = client.GetMessages(channel);
        std::vector<Stream> users = animeclub.GetUsers();

        for(int i=0; i<messages.size(); ++i)
            client.DeleteMessage(channel, messages[i]);
        // write more messages
        for(int i=users.size()-1; i>=0; --i) {
            client.SendMessage(channel, users[i].name + " is playing " + users[i].game + " with " + std::to_string(users[i].viewers) + " viewers!\n**" + users[i].title + "**\n" + users[i].url);
        }
        sleep(delay);
    }

    Destroy_CURL();
    return 0;

}

