//
// Created by adylewsk on 5/31/22.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "../headers/utils.hpp"
#include "Datas.h"

class Channel;

using namespace std;

class User : public Datas{

public:

typedef map<string, bool>::const_iterator channels_const_it; 

private:

    string _userName;

    string _nickName;

    string _ipAddress;

    int _port;

    map<string, bool> _channels; //chan

public:

    User();

    User(const string &userName, const string &nickName, const string &ipAddress, int port);

    virtual ~User();

    //GETTER

    //const string &getUserName() const;

    const string &getNickName() const;

    const string &getIpAddress() const;

    const int &getPort() const;

    const map<string, bool> &getChannels() const;

    const string &getChannel(const string &chanName) const;

    //SETTER

    void setNickName(const string &nickName);

    void setIpAddress(const string &ipAddress);

    void setPort(const int &port);

    void createChannel(Datas datasServ, const string &chanName, const int mode);

    void joinChannel(Datas datasServ, const string &chanName);

    void quitChannel(const string &chanName);

    void sendChanMessage();

    void sendPrivateMessage();
};


#endif //FT_IRC_USER_H
