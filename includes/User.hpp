#ifndef USER_H
#define USER_H

#include "datasException.hpp"
#include "Datas.hpp"
#include "utils.hpp"

typedef map<string, bool> userChannels;
typedef map<string, bool>::const_iterator userChannels_const_it;
typedef map<string, bool>::iterator userChannels_it;

class User : public Datas
{

	private:
		int	_step;

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

		// GETTERS

		const int &getStep() const;

		const string &getUserName() const;

		const string &getNickName() const;

		const string &getIpAddress() const;

		const int &getPort() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		// SETTERS

		void setUserName(usersDatas2 &users, const string &nickName);

		void setNickName(usersDatas2 &users, const string &nickName);

		void setIpAddress(const string &ipAddress);

		void setPort(const int &port);

		// UTILS

		void checkPwd(const string pwd, string arg);

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void fillUser(Datas &datas, string arg);

		void createChannel(Datas &datas, const string &chanName, const int mode);

		void joinChannel(Datas &datas, const string &chanName);

		void quitChannel(Datas &datas, const string &chanName);

		//    void sendChanMessage();

		//    void sendPrivateMessage();
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
