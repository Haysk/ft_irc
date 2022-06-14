#ifndef DATAS_H
# define DATAS_H

// #include "utils.hpp"
// #include "datasException.hpp"
// #include "PreUser.hpp"
// #include "Channel.hpp"
// #include "User.hpp"
#include "utils.hpp"
class User;
class Channel;
class PreUser;
typedef map<string, User *> usersDatas;
typedef map<string, Channel *> channelsDatas;
typedef map<int, PreUser *> preUsers;
typedef usersDatas::iterator usersDatas_it;
typedef usersDatas::const_iterator usersDatas_const_it;
typedef channelsDatas::iterator channelsDatas_it;
typedef channelsDatas::const_iterator channelsDatas_const_it;
typedef preUsers::iterator preUsers_it;
typedef preUsers::const_iterator preUsers_const_it;

class	Datas
{

	public:

		Datas(void);

		Datas(std::string &pwd);

		virtual ~Datas();

		Datas &operator=(const Datas &rhs);

		// GETTERS

		const usersDatas &getUsers() const;

		const channelsDatas &getChannels() const;

		User &getUser(const string &userName) const;

		Channel &getChannel(const string &chanName) const;

		const std::string &getPwd() const;

		// FUNCTIONS

		void newUser(const string &userName, const string &nickName, const string &ipAddress, int port);

		void newChannel(const string &chanName, const int mode, const string &userName);

		void addUserInChannel(const string &userName, const string &chanName, bool role);

		void removeUserFromChannel(const string &userName, const string &chanName);

		void deleteChannel(const string chanName);

		void newPreUser(int fd);

	private:
		usersDatas _usersDatas;		  // map (userName | userSettings)
		channelsDatas _channelsDatas; // map (chanName | chanSettings)
		preUsers _preUsers; // map (preUserFD | preUserSettings)
		const std::string _pwd;

};

#endif // DATAS_HPP
