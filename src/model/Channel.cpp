//
// Created by adylewsk on 5/31/22.
//

#include "Channel.h"


Channel::Channel(int mode, string userName): _mode(mode) {
    _users.insert(make_pair(userName, true));
}

Channel::~Channel() {

}

//GETTERS

int Channel::getMode() const {
    return _mode;
}

const map<string, bool> & Channel::getUsers() const {
    return _users;
}

map<string, bool>::const_iterator Channel::getUser(const string &userName) const {
    return Channel::_users.find(userName);
}

//SETTERS

void Channel::setMod(int mode) {
    _mode = mode;
}

void Channel::addUser(const string &userName, bool role = 0) {
    _users.insert(make_pair(userName, role));
}

void Channel::deleteUser(string &userName) {
    _users.erase(userName);
}
