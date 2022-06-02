//
// Created by adylewsk on 5/31/22.
//

#include "User.h"
#include "Channel.h"

User::User() {}

User::User(const string &nickName): _nickName(nickName) {}

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

const string &User::getPort() const {
    return _port;
}

const map<string, bool> &User::getChannels() const {
    return _channels;
}

//SETTER

void User::setNickName(const string &nickName) {
    _nickName = nickName;
}

void User::setIpAddress(const string &ipAddress) {
    _ipAddress = ipAddress;
}

void User::setPort(const string &port) {
    _port = port;
}

void User::addChannel(string chanName, bool role) {
    _channels.insert(make_pair(chanName, role));
}
