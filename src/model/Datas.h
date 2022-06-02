//
// Created by adylewsk on 6/2/22.
//

#ifndef FT_IRC_DATAS_H
#define FT_IRC_DATAS_H


#include "User.h"
#include "Channel.h"

class Datas {

private:

    map<string, User> _users; //pair userName | userSettings

    map<string, Channel> _channels; //pair chanName | chanSettings

public:
    Datas();

    virtual ~Datas();

    void addUser(const string &userName, User user);

    void newChannel(const string &userName, const string &chanName, Channel chan);
};


#endif //FT_IRC_DATAS_H
