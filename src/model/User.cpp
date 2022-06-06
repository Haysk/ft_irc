//
// Created by adylewsk on 5/31/22.
//

#include "User.h"
#include "Channel.h"

User::User() {}

User::User(const string &userName, const string &nickName, const string &ipAddress, int port) :
_userName(userName),
_nickName(nickName),
_ipAddress(ipAddress),
_port(port) {

}
User::~User() {}

//GETTER

//const string &User::getUserName() const {
//    return _userName;
//}

const string &User::getNickName() const {
    return _nickName;
}

const string &User::getIpAddress() const {
    return _ipAddress;
}

const int &User::getPort() const {
    return _port;
}

const map<string, bool> &User::getChannels() const {
    return _channels;
}

const string &User::getChannel(const string &chanName) const {
    channels_const_it it;
    it = _channels.find(chanName);
    if (it != _channels.end())
        return it->first;
    //throw
}

//SETTER

void User::setNickName(const string &nickName) {
    _nickName = nickName;
}

void User::setIpAddress(const string &ipAddress) {
    _ipAddress = ipAddress;
}

void User::setPort(const int &port) {
    _port = port;
}

void User::createChannel(Datas datasServ, const string &chanName, const int mode) {
    datasServ.newChannel(chanName, mode, _userName);
    _channels.insert(make_pair(chanName, true));
}

void User::joinChannel(Datas datasServ, const string &chanName) {
    datasServ.addUserInChannel(_userName, chanName, false);
}

void User::quitChannel(const string &chanName) {
    //try {
        getChannel(chanName);
        _channels.erase(chanName);
    //}
    //catch
    //trow exception
}
