//
// Created by adylewsk on 5/31/22.
//

#include "Channel.h"
#include "User.h"

Channel::Channel() {}

Channel::Channel(const string &chanName, int mode, const string &userName):
_chanName(chanName),
_mode(mode) {
    addUser(userName, true);
}

Channel::~Channel() {

}

Channel &Channel::operator=(const Channel &rhs) {
    this->_chanName = rhs.getChanName();
    this->_mode = rhs.getMode();
    this->_users = rhs.getUsers();
    return *this;
}

//GETTERS

string Channel::getChanName() const {
    return _chanName;
}

int Channel::getMode() const {
    return _mode;
}

map<string, bool> Channel::getUsers() const {
    return _users;
}

User &Channel::getUser(const string &userName) const {
    users_const_it it;
    it = _users.find(userName);
    if (it != _users.end()) {
        return Datas::getUser(it->first);
    }
    //throw exception
}

//SETTERS

void Channel::setChanName(const string newName) {
    _chanName = newName;
}

void Channel::setMod(int newMode) {
    _mode = newMode;
}

void Channel::addUser(const string userName, bool role = false) {
    //try {
    // getUser(userName);
    // throw exception
    //}
    //catch { if chan doesn't exist
    _users.insert(make_pair(userName, role));
    //}
}

void Channel::deleteUser(const string userName) {
    //try {
    getUser(userName).quitChannel(_chanName);
    _users.erase(userName);
    //}
    //trow exception
}

