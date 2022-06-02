//
// Created by adylewsk on 5/31/22.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "../headers/utils.hpp"

class Channel;

using namespace std;

class User {

private:

    //string _userName;

    string _nickName;

    string _ipAddress;

    string _port;

    map<string, bool> _channels; //chan

public:

    User();

    User(const string &nickName);

    virtual ~User();

    //GETTER

    //const string &getUserName() const;

    const string &getNickName() const;

    const string &getIpAddress() const;

    const string &getPort() const;

    const map<string, bool> &getChannels() const;

    //SETTER

    void setNickName(const string &nickName);

    void setIpAddress(const string &ipAddress);

    void setPort(const string &port);

    void addChannel(string chanName, bool role);
};


#endif //FT_IRC_USER_H
