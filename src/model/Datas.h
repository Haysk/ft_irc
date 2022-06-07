#ifndef FT_IRC_DATAS_H
#define FT_IRC_DATAS_H

#include "../include/utils.hpp"

class User;
class Channel;

class Datas
{

public:

	typedef map<string, User *> usersDatas;
	typedef map<string, Channel *> channelsDatas;
	typedef usersDatas::iterator usersDatas_it;
	typedef usersDatas::const_iterator usersDatas_const_it;
	typedef channelsDatas::iterator channelsDatas_it;
	typedef channelsDatas::const_iterator channelsDatas_const_it;

private:

	usersDatas _usersDatas;		  // map (userName | userSettings)
	channelsDatas _channelsDatas; // map (chanName | chanSettings)

public:

	Datas();

	virtual ~Datas();

	Datas &operator=(const Datas &rhs);

	// GETTERS

	const usersDatas &getUsers() const;

	const channelsDatas &getChannels() const;

	User &getUser(const string &userName) const;

	Channel &getChannel(const string &chanName) const;

	// FUNCTIONS

	void newUser(const string &userName, const string &nickName, const string &ipAddress, int port);

	void newChannel(const string &chanName, const int mode, const string &userName);

	void addUserInChannel(const string &userName, const string &chanName, bool role);

	void removeUserFromChannel(const string &userName, const string &chanName);

	void deleteChannel(const string chanName);

	//EXCEPTIONS

public :
		class datasException : public exception
		{
			const char *_msg;

		public:
			datasException(const char *msg) : _msg(msg) {
			}

			const char *what() const throw (){ return _msg; }
		};
};

#endif // FT_IRC_DATAS_H
