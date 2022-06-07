#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include "../include/utils.hpp"
#include "Datas.h"

class User;

class Channel : public Datas
{

public:

	typedef map<string, bool> usersInChannel;
	typedef map<string, bool>::const_iterator usersInChannel_const_it;

private:

	string _chanName;

	int _mode;

	usersInChannel _users; // map (userName | role)

	Channel();

public:

	Channel(const string &chanName, int mode, const string &userName);

	virtual ~Channel();

	Channel &operator=(const Channel &rhs);

	// GETTERS

	string getChanName() const;

	int getMode() const;

	usersInChannel getUsers() const;

	User &getUser(const string &userName) const;

	bool userIsOperator(const string &userName) const;

	// SETTERS

	void setChanName(const string newName);

	void setMod(int newMode);

	// FUNCTIONS

	void addUser(const string userName, bool role);

	void deleteUser(const string userName);
	
	//EXCEPTIONS

public:	
	class channelException : public exception
	{
		const char *_msg;

	public:
		channelException(const char *msg) : _msg(msg) {
		}

		const char *what() const throw (){ return _msg; }
	};
};

#endif // FT_IRC_CHANNEL_H
