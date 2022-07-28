#ifndef CHANNEL_H
#define CHANNEL_H

#include "datasException.hpp"
#include "Datas.hpp"
#include "utils.hpp"

typedef map<string, bool> 					usersInChannel;
typedef map<string, bool>::iterator			usersInChannel_it;
typedef map<string, bool>::const_iterator	usersInChannel_const_it;

class Channel : public Datas
{
	private:
		Datas			*_datasPtr;

		string			_chanName;

		string			_topic;

		int				_mode;

		usersInChannel	_users; // map (userName | role)

		usersInChannel	_inactiveUsers;

		vector<string>	_invit;

	public:

		Channel();

		Channel(Datas *datasPtr, const string &chanName, int mode, const string &userName);

		virtual			~Channel();

		Channel			&operator=(const Channel &rhs);

	// GETTERS

		Datas			*getDatasPtr() const;

		string			getChanName() const;

		string			getTopic() const;

		int 			getMode() const;

		usersInChannel	getUsers() const;

		usersInChannel	getInactiveUsers() const;

		User			&getInactiveUser(const string &userName) const;

		vector<string>	getInvit(void) const;

		bool			chanModeIs(const int mode) const;

		User 			&getUser(const string &userName) const;

		bool			userIsChanOp(const string &userName) const;

	// SETTERS

		void 			setTopic(const string &newTopic);

		void 			setMod(const int newMode, const bool add);

		void 			setInvit(const string &userName);

	// FUNCTIONS

		void 			addUser(const string &userName, bool role);

		void 			useInvit(const string &userName);

		void 			deleteUser(const string &userName);

		void 			activeToInactiveUser(const string &userName);

		void 			inactiveToActiveUser(const string &userName);

		void 			responseCmdToAllInChan(User& joiner, const std::string& msg);

		void 			responseCmdToDestInChan(User& joiner, const std::string& msg);

		void 			sendModeChannel(User& user);
};

ostream& operator<<(ostream& os, const Channel& rhs);

#endif // CHANNEL_HPP
