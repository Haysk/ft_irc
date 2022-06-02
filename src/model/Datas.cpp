//
// Created by adylewsk on 6/2/22.
//

#include "Datas.h"

Datas::Datas() {}

Datas::~Datas() {

}

void Datas::addUser(const string &userName, User user) {
    _users.insert(make_pair(userName, user));
}

void Datas::newChannel(const string &userName, const string &chanName, Channel chan) {
    _channels.insert(make_pair(chanName, chan));
    _users.find(userName)->second.addChannel(chanName, 1);
}
