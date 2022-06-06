//
// Created by adylewsk on 6/2/22.
//

#include "Datas.h"
#include "User.h"
#include "Channel.h"

Datas::Datas() {}

Datas::~Datas() {

}

const Datas::usersTab &Datas::getUsers() const {
    return _usersTab;
}

const Datas::channelsTab &Datas::getChannels() const {
    return _channelsTab;
}

User &Datas::getUser(const string &userName) const {
    usersDatas_const_it it;
    
    it = _usersTab.find(userName);
    if (it != _usersTab.end())
        return it->second;
    //throw exception
}

Channel &Datas::getChannel(const string &chanName) const {
    channelsDatas_const_it it;

    it = _channelsTab.find(chanName);
    if (it != _channelsTab.end())
        return it->second;
    //throw exception
}

void Datas::newUser(const string &userName, const string &nickName, const string &ipAddress, int port) {
    //try {
    // getUser(userName);
    // throw exception
    //}
    //catch { if chan doesn't exist
    User *user;
    user = new User(userName, nickName, ipAddress, port);
    _usersTab.insert(make_pair(userName, user));
    //}
}

void Datas::newChannel(const string &chanName, const int mode, const string &userName) {
    //try {
    // getChannel(chanName);
    // throw exception
    //}
    //catch { if chan doesn't exist
    Channel *chan;
    chan = new Channel(chanName, mode, userName);
    _channelsTab.insert(make_pair(chanName, chan));
    //}
}

void Datas::addUserInChannel(const string &userName, const string &chanName, bool role = false) {
    //try {
    // getChannel(chanName);
    // throw exception
    //}
    //catch { if chan doesn't exist
    getChannel(chanName).addUser(userName, role);
    //}
}
