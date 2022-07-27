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

		bool	_co;

		bool	_op;

		string _password;

		string	_userName;

		string	_nickName;

		string	_hostName;

		string	_serverName;

		string	_realName;

//		string	_activeChannel;

		userChannels _channels; // map (chanName | role)

	public:
		User();

		User(Datas *datasPtr, int fd);

		virtual ~User();

		User &operator=(const User &rhs);

		// GETTERS

		const int &getFd() const;

		const int &getStep() const;

		const string &getUserName() const;

		const string &getNickName() const;

		const string &getActiveChannel() const;

		const userChannels &getChannels() const;

		Channel &getChannel(const string &chanName) const;

		const bool &getOp() const;

		bool &getOp(const string &chanName);
		
		bool getCo(void);

		// REGISTRATION

		void initUserName(string &userCmd);

		void checkCAPLS(string &arg);

		void checkPwd(const string pwd, string &arg);

		void fillUser(string &arg);

		// UTILS

		void addChannel(const string &chanName, bool role);

		// FUNCTIONS

		void execCmd(const string &cmd);

		void createChannel(const string &chanName, const int mode);

		void join(const string &chanName);

		void part(const string &chanName);

		void quit(const std::string& msg);

		void nick(const std::string& nickName);

		void deleteChannel(const string &chanName);

		void privMsg(const string  &destName, const string &message);

		map<string, vector<string> > names(const vector<string> &channels = vector<string>());

		void sendRegistrationComplete(void);

		// CHAN OPERATOR FUNCTION

		void kick(const string &userName, const string &chanName);

		void mode(const string &chanName, const int chanMode, const bool add);

		void topic(const string &chanName, const string &newChanName);

		void invite(const string &userName, const string &chanName);
};

ostream& operator<<(ostream& os, const User& rhs);

#endif //USER_HPP
