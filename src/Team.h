#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>

struct Stream { 
    std::string url;
    std::string game;
    std::string name;
    std::string title;
    int         viewers;
    int         followers;
};

class Team {

  private:
    std::string              url;

  public:
                             Team(std::string);

    std::vector<Stream> GetUsers(bool deep = false);
};

#endif

