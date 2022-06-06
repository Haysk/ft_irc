//
// Created by adylewsk on 5/31/22.
//

#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include "../headers/utils.hpp"
#include "Datas.h"

class User;

class Channel : public Datas {

public:

    typedef map<string, bool>::const_iterator users_const_it;

private:

    string _chanName;

    int _mode;

    map<string, bool> _users; // pair array (userName, role)

    Channel();

public:

    Channel(const string &chanName, int mode, const string &userName);

    virtual ~Channel();

    Channel &operator=(const Channel &rhs);

    //GETTER

    string getChanName() const;

    int getMode() const;

    map<string, bool> getUsers() const;

    User &getUser(const string &userName) const;

    //SETTER

    void setChanName(const string newName);

    void setMod(int newMode);

    void addUser(const string userName , bool role);

    void deleteUser(const string userName);
};

#endif //FT_IRC_CHANNEL_H
