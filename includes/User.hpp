#ifndef USER_H
#define USER_H

#include "datasException.hpp"
#include "Datas.hpp"
#include "utils.hpp"
#include "Command.hpp"

typedef map<string, bool> userChannels;
typedef map<string, bool>::const_iterator userChannels_const_it;
typedef map<string, bool>::iterator userChannels_it;

class User : public Datas
{

	private:
		int	_step;

		string _userName;

		string _nickName;

		userChannels _channels; // map (chanName | role)

	public:
		User();

		virtual ~User();

		User &operator=(const User &rhs);

		// GETTERS

		const int &getStep() const;

		const string &getUserName() const;

		const string &getNickName() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		// SETTERS

		void setUserName(const usersDatas &users, const string &nickName);

		void setNickName(const usersDatas &users, const string &nickName);

		// UTILS

		void checkPwd(const string pwd, string arg);

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void fillUser(Datas &datas, string arg);

		void execCmd(Datas &datas, string cmd);

		void createChannel(Datas &datas, const string &chanName, const int mode);

		void joinChannel(Datas &datas, const string &chanName);

		void quitChannel(Datas &datas, const string &chanName);

		//    void sendChanMessage();

		//    void sendPrivateMessage();
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
