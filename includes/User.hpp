#ifndef USER_H
#define USER_H

#include "utils.hpp"
#include "datasException.hpp"
#include "Datas.hpp"
#include "Channel.hpp"
#include "PreUser.hpp"

typedef map<string, bool> userChannels;
typedef map<string, bool>::const_iterator userChannels_const_it;
typedef map<string, bool>::iterator userChannels_it;

class User : public Datas 
{

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

		// GETTERS

		const string &getUserName() const;

		const string &getNickName() const;

		const string &getIpAddress() const;

		const int &getPort() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		// SETTERS

		void setNickName(const string &nickName);

		void setIpAddress(const string &ipAddress);

		void setPort(const int &port);

		// UTILS

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void createChannel(Datas &datas, const string &chanName, const int mode);

		void joinChannel(Datas &datas, const string &chanName);

		void quitChannel(Datas &datas, const string &chanName);

		//    void sendChanMessage();

		//    void sendPrivateMessage();
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
