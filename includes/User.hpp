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
		Datas *_datasPtr;

		int		_fd;

		int		_step;

		bool	_op;

		string	_userName;

		string	_nickName;

		userChannels _channels; // map (chanName | role)

	public:
		User(Datas *datasPtr, int fd);

		virtual ~User();

		User &operator=(const User &rhs);

		// GETTERS

		const int &getFd() const;

		const int &getStep() const;

		const string &getUserName() const;

		const string &getNickName() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		const bool &getOp() const;

		// REGISTRATION

		std::string initUserName(string &userCmd);

		std::string initNickName(const usersDatas &users, string &nickCmd);

		std::string checkCAPLS(string &arg);

		std::string checkPwd(const string pwd, string &arg);

		const string fillUser(string &arg);

		// UTILS

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void execCmd(const string &cmd);

		void createChannel(const string &chanName, const int mode);

		void joinChannel(const string &chanName);

		void quitChannel(const string &chanName);

		void deleteChannel(const string &chanName);

		//    void sendChanMessage();

		//    void sendPrivateMessage();

		map<string, vector<string> > names(const vector<string> &channels = vector<string>());

		// CHAN OPERATOR FUNCTION

		void kick(const string &userName, const string &chanName);

		void mode(const string &chanName, const int chanMode, const bool add);

		void topic(const string &chanName, const string &newChanName);

		void invite(const string &userName, const string &chanName);
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
