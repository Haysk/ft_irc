#ifndef DATAS_H
# define DATAS_H

#include "utils.hpp"

class User;
class Channel;

typedef map<int, User *> usersDatas;
typedef map<string, Channel *> channelsDatas;

typedef usersDatas::iterator usersDatas_it;
typedef usersDatas::const_iterator usersDatas_const_it;

typedef channelsDatas::iterator channelsDatas_it;
typedef channelsDatas::const_iterator channelsDatas_const_it;

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
		
		void newUser(int fd);

		void treatCmd(int fd, string cmd);

		void newChannel(const string &chanName, const int mode, const string &userName);

		void addUserInChannel(const string &userName, const string &chanName, bool role);

		void removeUserFromChannel(const string &userName, const string &chanName);

		void deleteChannel(const string chanName);

	private:
		usersDatas _usersDatas;		  // map (userFD | userSettings)
		channelsDatas _channelsDatas; // map (chanName | chanSettings)
		const std::string _pwd;

};

#endif // DATAS_HPP
