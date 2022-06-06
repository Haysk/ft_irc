//
// Created by adylewsk on 6/2/22.
//

#ifndef FT_IRC_DATAS_H
#define FT_IRC_DATAS_H

#include "../headers/utils.hpp"

class User;
class Channel;

class Datas {

public:
    typedef map<string, User &> usersTab;
    typedef map<string, Channel &> channelsTab;
    typedef usersTab::iterator usersDatas_it;
    typedef usersTab::const_iterator usersDatas_const_it;
    typedef channelsTab::iterator channelsDatas_it;
    typedef channelsTab::const_iterator channelsDatas_const_it;

private:

    usersTab _usersTab; //pair userName | userSettings
    channelsTab _channelsTab; //pair chanName | chanSettings

public:

    Datas();

    virtual ~Datas();

    const usersTab &getUsers() const;

    const channelsTab &getChannels() const;

    User &getUser(const string &userName) const;

    Channel &getChannel(const string &chanName) const;

    void newUser(const string &userName, const string &nickName, const string &ipAddress, int port);

    void newChannel(const string &chanName, const int mode, const string &userName);

    void addUserInChannel(const string &userName, const string &chanName, bool role);

    void removeUserFromChannel();
};


#endif //FT_IRC_DATAS_H
