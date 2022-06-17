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
		int	_fd;

		int	_step;

		string _userName;

		string _nickName;

		userChannels _channels; // map (chanName | role)

	public:
		User(int);

		virtual ~User();

		User &operator=(const User &rhs);

		// GETTERS

		const int &getFd() const;

		const int &getStep() const;

		const string &getUserName() const;

		const string &getNickName() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		// REGISTRATION

		std::string initUserName(const usersDatas &users, string &userName);

		std::string initNickName(const usersDatas &users, string &nickName);

		std::string checkCAPLS(string arg);

		std::string checkPwd(const string pwd, string arg);

		std::string fillUser(Datas &datas, string arg);


		// SETTERS

		// UTILS

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void execCmd(Datas &datas, string cmd);

		void createChannel(Datas &datas, const string &chanName, const int mode);

		void joinChannel(Datas &datas, const string &chanName);

		void quitChannel(Datas &datas, const string &chanName);

		//    void sendChanMessage();

		//    void sendPrivateMessage();
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
