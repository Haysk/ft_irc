#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "../include/utils.hpp"
#include "Datas.h"

class Channel;

using namespace std;

class User : public Datas{

public:

typedef map<string, bool> userChannels;
typedef map<string, bool>::const_iterator userChannels_const_it;
typedef map<string, bool>::iterator userChannels_it;

private:

    string _userName;

    string _nickName;

    string _ipAddress;

    int _port;

    userChannels _channels; // map (chanName | role)

public:

    User();

    User(const string &userName, const string &nickName, const string &ipAddress, int port);

    virtual ~User();

    User &operator=(const User &rhs);

    //GETTERS

    const string &getUserName() const;

    const string &getNickName() const;

    const string &getIpAddress() const;

    const int &getPort() const;

    const userChannels &getChannels() const;

    Channel &getChannel(const string &chanName) const;

    //SETTERS

    void setNickName(const string &nickName);

    void setIpAddress(const string &ipAddress);

    void setPort(const int &port);

    //FUNCTIONS

    void createChannel(Datas &datas, const string &chanName, const int mode);

    void joinChannel(Datas &datas, const string &chanName);

    void quitChannel(Datas &datas, const string &chanName);

//    void sendChanMessage();

//    void sendPrivateMessage();

	//EXCEPTIONS

public:	
	class userException : public exception
	{
		const char *_msg;

	public:
		userException(const char *msg) : _msg(msg) {
		}

		const char *what() const throw (){ return _msg; }
	};
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //FT_IRC_USER_H
