//
// Created by adylewsk on 5/31/22.
//

#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include "../headers/utils.hpp"
#include "User.h"


class Channel {

private:

    int _mode;

    map<string, bool> _users; // pair array (userName, role)

public:

    Channel(int mode, string userName);

    virtual ~Channel();

    //GETTER

    int getMode() const;

    const map<string, bool> &getUsers() const;

    map<string, bool>::const_iterator getUser(const string &userName) const;

    //SETTER

    void setMod(int mode);

    void addUser(const string &userName, bool role);

    void deleteUser(string &userName);
};

#endif //FT_IRC_CHANNEL_H
