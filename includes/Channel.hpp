#ifndef CHANNEL_H
#define CHANNEL_H

#include "datasException.hpp"
#include "Datas.hpp"
#include "utils.hpp"

typedef map<string, bool> usersInChannel;
typedef map<string, bool>::iterator usersInChannel_it;
typedef map<string, bool>::const_iterator usersInChannel_const_it;

class Channel : public Datas
{
	private:
		Datas *_datasPtr;

		string _chanName;

		int _mode;

		usersInChannel _users; // map (userName | role)

		vector<string> _invit;

	public:

		Channel();

		Channel(Datas *datasPtr, const string &chanName, int mode, const string &userName);

		virtual ~Channel();

		Channel &operator=(const Channel &rhs);

		// GETTERS

		string getChanName() const;

		int getMode() const;

		bool chanModeIs(const int mode) const;

		usersInChannel getUsers() const;

		User &getUser(const string &userName) const;

		bool userIsChanOp(const string &userName) const;

		bool userIsActive(const string &userName);

		Datas *getDatasPtr(void);

		// SETTERS

		void setChanName(const Datas &datas, const string &newName);

		void setMod(const int newMode, const bool add);

		void setInvit(const string &userName);

		// FUNCTIONS

		void addUser(const string &userName, bool role);

		void deleteUser(const string &userName, bool config);

		void useInvit(const string &userName);

		void displayInterface(const int& fd);
};

ostream& operator<<(ostream& os, const Channel& rhs);

#endif // CHANNEL_HPP
