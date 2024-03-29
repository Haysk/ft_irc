#include "../includes/User.hpp"
#include "../includes/Channel.hpp"

User::User() {};

User::User(Datas *datasPtr, int fd): _datasPtr(datasPtr), _fd(fd), _step(1), _co(true), _op(0) {}

User::~User()
{
	_channels.clear();
}

User &User::operator=(const User &rhs)
{
	_userName = rhs.getUserName();
	_nickName = rhs.getNickName();
	_fd = rhs.getFd();
	_step = rhs.getStep();
	_channels = rhs.getChannels();
	return *this;
}

// GETTERS

Datas*	User::getDatasPtr(void)
{
	return (_datasPtr);
}

const int &User::getFd() const
{
	return _fd;
}

const int &User::getStep() const
{
	return _step;
}

const string &User::getUserName() const
{
	return _userName;
}

const string &User::getNickName() const
{
	return _nickName;
}

const userChannels &User::getChannels() const
{
	return _channels;
}

Channel &User::getChannel(const string &chanName) const
{
	userChannels_const_it it;
	it = _channels.find(chanName);
	if (it != _channels.end())
		return Datas::getChannel(it->first);
	throw datasException("User not in " + chanName + "Channel", _userName);
}

const bool &User::getOp() const
{
	return _op;
}

bool &User::getOp(const string &chanName)
{
	getChannel(chanName);
	return (_channels[chanName]);
}

bool	User::getCo(void)
{
	return (_co);
}

// SETTERS

void	User::initUserName(string &userCmd)
{
	std::string	name;
	const usersDatas	&users = _datasPtr->getUsers();
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();

	if (!checkCmdName(userCmd, "USER"))
		throw std::invalid_argument("You've to send us: USER <username> <unused> <unused> <:realname>");
	checkUserCmdNbrArg(userCmd, " ");
	name = getArgAt(userCmd, 1, " ", 0);
	checkLenArg(name, 9);
	isAlphaNum(name);
	_hostName = getArgAt(userCmd, 2, " ", 0);
	_serverName = getArgAt(userCmd, 3, " ", 0);
	isAlphaNum(_serverName);
	_realName = getArgAt(userCmd, 4, " ", 1);
	isAlphaNumSp(_realName);
	while (it != ite)
	{
		if (!it->second->getUserName().compare(name))
			throw datasException(name + " :Username is already in use");
		it++;
	}
	for (map<string, string>::const_iterator it = _datasPtr->getOperatorConf().begin(), ite = _datasPtr->getOperatorConf().end();
			it != ite; it++)
	{
		if (it->second == _password && it->first == name)
		{
			_userName = name;
			_op = true;
			sendRegistrationComplete();
		}
		if (it->first == name)
			throw datasException("Registration has failed");
	}
	if (_password != _datasPtr->getPwd())
		throw datasException("Operator registration has failed");
	_userName = name;
	sendRegistrationComplete();
}

void	User::nick(const string &nickCmd)
{
	const usersDatas	&users = _datasPtr->getUsers();
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();
	std::string	nickname;
	std::string	prevNick = _nickName;

	if (!checkCmdName(nickCmd, "NICK"))
		throw std::invalid_argument("You've to send us: NICK <nickname>");
	checkRangeArg(nickCmd, 2, 2);
	try
	{
		nickname = getArgAt(nickCmd, 1, " ", 0);
	}
	catch (datasException& e)
	{
		(void)e;
		throw datasException(":No nickname given", 431);
	}
	try {
		checkLenArg(nickname, 9);
		isAlphaNum(nickname);
	}
	catch (exception &e) {
		throw datasException(nickname + " :Erroneous nickname");
	}
	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickname))
			throw datasException(" :Nickname is already in use");
		it++;
	}
	_nickName = nickname;
	if (prevNick.length())
		_datasPtr->responseToCmd(*this, "NICK :" + nickname, 0 ,prevNick);
}

// UTILS

void	User::checkCAPLS(std::string &arg)
{
	if (getArgAt(arg, 0, " ", 0).compare("CAP")
			|| getArgAt(arg, 1, " ", 0).compare("LS"))
		throw std::invalid_argument("You've to send us: CAP LS");
}

void	User::checkPwd(const std::string pwd, std::string &pwdLine)
{
	std::string	pwdSent;

	if (!checkCmdName(pwdLine, "PASS"))
		throw std::invalid_argument("You've to send us: PASS <password>");
	checkNbrArg(pwdLine, 2);
	pwdSent = getArgAt(pwdLine, 1, " ", 0);
	for (map<string, string>::const_iterator it = _datasPtr->getOperatorConf().begin(), ite = _datasPtr->getOperatorConf().end();
			it != ite; it++)
	{
		if (!it->second.compare(pwdSent))
		{
			_password = pwdSent;
		}
	}
	if (pwdSent.compare(0, strlenP(pwdSent), pwd))
        throw std::invalid_argument("The password passed isn't valid");
    _password = pwdSent;
}

void	User::addChannel(const string &chanName, bool role) {
	if (!_channels.insert(make_pair(chanName, role)).second)
		throw datasException("User already in " + chanName , _userName);
}

// FUNCTIONS

void	User::fillUser(string &arg)
{
	string	cmd = getArgAt(arg, 0, " ", 0);

	if (!cmd.compare("/quit"))
		quit(arg.substr(cmd.length()));
	switch (_step) {
		case 1:
			checkCAPLS(arg);
			break;
		case 2:
			checkPwd(_datasPtr->getPwd(), arg);
			break;
		case 3:
			nick(arg);
			break;
		case 4:
			initUserName(arg);
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
}

void	User::execCmd(const string &cmd)
{
	_datasPtr->clearCmd();
	_datasPtr->getCmd().buildCmd(countOccurrences(" ", cmd) - 1, cmd);
	_datasPtr->getCmd().checkCmd(*this);
}

void	User::createChannel(const string &chanName, const int mode)
{
	_datasPtr->newChannel(chanName, mode, _userName);
	_channels.insert(make_pair(chanName, true));
}

void	User::join(const string &chanName)
{
	if (chanName.empty() || chanName[0] != '#')
		throw datasException("Channel name must start with #");
	try {
		createChannel(chanName, 0);
		_datasPtr->sendJoinMsgs(*this, _datasPtr->getChannel(chanName));
	} catch (datasException &e) {
		Channel &chan = _datasPtr->getChannel(chanName);
		if (_op)
			_datasPtr->addUserInChannel(_userName, chanName, true); // ERR_INVITEONLYCHAN
		else
			_datasPtr->addUserInChannel(_userName, chanName, false); // ERR_INVITEONLYCHAN
		_datasPtr->sendJoinMsgs(*this, _datasPtr->getChannel(chanName));
		if (chan.chanModeIs(MODE_T))
			topic(chanName);
	}
}

void	User::part(const string &chanName, const string &msg)
{
	_datasPtr->removeUserFromChannel(_userName, chanName, msg, 0, *this); // ERR_NOSUCHCHANNEL ERR_NOTONCHANNEL
}

void	User::quit(const std::string& msg)
{
	_co = false;
	_datasPtr->responseToCmd(*this, "QUIT : " + msg);

	userChannels::const_iterator	it = _channels.begin();

	for (size_t i = _channels.size(); i > 0; i--) {
		part(it->first, msg);
		it = _channels.begin();
	}
	if (msg.length())
		std::cout << "<" + _userName + "> " + msg << std::endl;
	else
		std::cout << "<" + _userName + "> HAS LEFT THE SERVER" << std::endl;
}

void	User::deleteChannel(const string &chanName)
{
	if (_channels.erase(chanName) <= 0)
		throw datasException("User not in this Channel", _userName);
}

void User::privMsg(const string &destName, const string &message) {
	if (message.empty())
		throw datasException(destName + " :No text to send", 412);
	if (!destName.empty() && destName[0] != '#') {
		User &dest = _datasPtr->getUser(destName, NICKNAME);
		_datasPtr->responseToCmd(*this, "PRIVMSG " + destName + " " + message, dest.getFd());
	}
	if  (!destName.empty() && destName[0] == '#')
	{
		try {
			Channel &dest = _datasPtr->getChannel(destName);
			dest.getUser(_userName);
			dest.responseCmdToDestInChan(*this, "PRIVMSG " + destName + " " + message);
		} catch (datasException &e) {
			if (!string(e.getOption()).compare("403"))
				throw datasException(":No recipient given (PRIVMSG)", 411); // ERR_NORECIPIENT
			if (!string(e.getOption()).compare("442"))
				throw datasException(destName + " :Cannot send to channel", 404); // ERR_CANNOTSENDTOCHAN
		}
	}
}

void User::notice(const string &destName, const string &message) {
	if (message.empty())
		return;
	if (!destName.empty() && destName[0] != '#') {
		User &dest = _datasPtr->getUser(destName, NICKNAME);
		_datasPtr->responseToCmd(*this, "NOTICE " + destName + " " + message, dest.getFd());
	}
	if  (!destName.empty() && destName[0] == '#')
	{
		try {
			Channel &dest = _datasPtr->getChannel(destName);
			dest.getUser(_userName);
			dest.responseCmdToDestInChan(*this, "NOTICE " + destName + " " + message);
		} catch (datasException &e) {}
	}

}

void	User::sendRegistrationComplete(void)
{
	std::string msg = ":ircserv 001 " + _nickName + " :Welcome to ircserv, " + _nickName;
	msg += "\n:ircserv 002 " + _nickName + " :Your host is ircserv, running version ircd";
	msg += "\n:ircserv 003 " + _nickName + " :This server was created Fri Apr 10 2017 at 16:33:19 UTC";
	msg += "\n:ircserv 004 " + _nickName + " ircserv HHA_entreprise";
	sendMsgToClient(_fd, msg);
}

// CHAN OPERATOR FUNCTION

void	User::kick(const string &nickName, const string &chanName, string &msg)
{
	User &user = _datasPtr->getUser(nickName, NICKNAME);
	Channel &chan = _datasPtr->getChannel(chanName); // ERR_NOSUCHCHANNEL

	if (!chan.userIsChanOp(_userName)) // ERR_NOTONCHANNEL
		throw datasException(chanName + " :You're not channel operator", 482); // ERR_CHANOPRIVSNEEDED
    if (user.getOp())
		throw datasException(chanName + ":Permission Denied- You're not an IRC operator", 481); // ERR_NOPRIVILEGES ????????????????????????
	try {
		chan.getUser(user.getUserName());
	} catch (datasException &e) {
		throw datasException(chanName + " :They aren't on that channel", 441); // ERR_USERNOTINCHANNEL
	}
	if (!msg.length())
		msg = "no reason";
	_datasPtr->removeUserFromChannel(user.getUserName(), chanName, msg, 1, *this);
	chan.responseCmdToAllInChan(*this, "KICK " + chanName + " " + nickName + " :" + msg);
}

void	User::mode(const string &chanName, const int chanMode, const bool add,
			const string& strMode)
{
	Channel	&chan = _datasPtr->getChannel(chanName);
	bool isOp;

	if (chanMode == -1)
	{
		chan.sendModeChannel(*this);
		return;
	}
	try {
		isOp = chan.userIsChanOp(_userName);
	} catch (datasException &e){
		throw datasException(chanName + " :You're not on that channel", 442); // ERR_USERNOTINCHANNEL
	}
	if (!isOp)
		throw datasException(chanName + " :You're not channel operator", 482); // ERR_CHANOPRIVSNEEDED
	chan.setMod(chanMode, add);
	chan.responseCmdToAllInChan(*this, "MODE " + chanName + " " + strMode);
}

void	User::invite(const string &nickName, const string &chanName)
{
	Channel &chan = _datasPtr->getChannel(chanName); // ERR_NOSUCHCHANNEL

	if (!chan.userIsChanOp(_userName)) // ERR_NOTONCHANNEL
		throw datasException(chanName + " :You're not channel operator", 482); // ERR_CHANOPRIVSNEEDED
	if (!chan.chanModeIs(MODE_I))
		throw datasException(chanName+ " :Channel doesn't support modes", 477); // ERR_NOCHANMODES

	User &usr = _datasPtr->getUser(nickName, NICKNAME); // ERR_NOSUCHNICK
	chan.setInvit(usr.getUserName()); // ERR_USERONCHANNEL

	_datasPtr->sendMsgByServerToExecuter(*this, "341 " + _nickName + " " + nickName + " " + chanName);
	_datasPtr->responseToCmd(*this, "INVITE " + _nickName + " :" + chanName, _datasPtr->getUser(nickName, NICKNAME).getFd());
}

void	User::topic(const string &chanName, const string &newTopicName)
{
	Channel &chan = _datasPtr->getChannel(chanName);
	chan.getUser(_userName); // ERR_NOTONCHANNEL
	if (newTopicName.empty())
	{
		if (chan.getTopic().empty())
			sendMsgToClient(_fd ,chanName + " :No topic is set"); // RPL_NOTOPIC
		else
			chan.responseToCmd(*this, "TOPIC " + chanName + " " + chan.getTopic());
		return;
	}
	_datasPtr->newChannelTopic(_userName, chanName, newTopicName); // ERR_CHANOPRIVSNEEDED ERR_NOCHANMODES
	chan.responseCmdToAllInChan(*this, "TOPIC " + chanName + " " + chan.getTopic());
}

ostream&	operator<<(ostream& os, const User& rhs)
{
	os << "\n" << rhs.getUserName() << ":\n\tNick Name : \t" << rhs.getNickName();
	os << "\n" << "\tfd : \t" << rhs.getFd();
	os << "\n" << "\tstep : \t" << rhs.getStep();
	os << "\n\tChannels :\n";
	const userChannels &channels = rhs.getChannels();
	for (userChannels_const_it it = channels.begin(); it != channels.end(); it++)
		os << "\t\t\t" << it->first << "\n\t\t\trole : " << it->second << endl << endl;
	return (os);
}
