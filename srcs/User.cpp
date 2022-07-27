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
	_activeChannel = rhs.getActiveChannel();
	_channels = rhs.getChannels();
	return *this;
}

// GETTERS

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

const string &User::getActiveChannel() const
{
	return _activeChannel;
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

	checkCmdName(userCmd, "USER");
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

	checkCmdName(nickCmd, "NICK");
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
	checkLenArg(nickname, 9);
	//	check nickname syntaxe ERR_ERRONEUSNICKNAME
	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickname))
			throw datasException(nickname + " :Nickname is already in use");
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

	checkCmdName(pwdLine, "PASS");
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
			// JE NE COMPRENDS PAS
			try {
				initUserName(arg);
			} catch (datasException &e) {
				sendMsgToClient(_fd, "ERROR: " + string(e.what()));
				_step--;
			}
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
}

void	User::execCmd(const string &cmd)
{
	_datasPtr->clearCmd();
	_datasPtr->getCmd().buildCmd(countOccurrences(" ", cmd), cmd);
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
		_activeChannel = chanName;
		_datasPtr->sendJoinMsgs(*this, _datasPtr->getChannel(chanName));
	} catch (datasException &e) {
		try {
			_datasPtr->getChannel(chanName).getUser(_userName);
			if (_activeChannel != chanName) {
				_activeChannel = chanName;
				_datasPtr->sendJoinMsgs(*this, _datasPtr->getChannel(chanName));
			}
		} catch (datasException &e) {
			if (_op)
				_datasPtr->addUserInChannel(_userName, chanName, true); // ERR_INVITEONLYCHAN
			else
				_datasPtr->addUserInChannel(_userName, chanName, false); // ERR_INVITEONLYCHAN
			_activeChannel = chanName;
			_datasPtr->sendJoinMsgs(*this, _datasPtr->getChannel(chanName));
		}
	}
}

void	User::part(const string &chanName)
{
	_datasPtr->removeUserFromChannel(_userName, chanName); // ERR_NOSUCHCHANNEL ERR_NOTONCHANNEL
}

void	User::quit(const std::string& msg)
{
	_co = false;
	if (msg.length())
		std::cout << "<" + _userName + "> " + msg << std::endl;
	else
		std::cout << "<" + _userName + "> HAS LEFT THE SERVER" << std::endl;
}

void	User::deleteChannel(const string &chanName)
{
	if (_channels.erase(chanName) <= 0)
		throw datasException("User not in this Channel", _userName);
	if (chanName == _activeChannel)
		_activeChannel = "";

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

map<string, vector<string> > User::names(const vector<string> &channels)
{
	map<string, vector<string> > list;

	for (vector<string>::const_iterator it = channels.begin(), ite = channels.end(); it != ite; it++)
	{
		cout << *it.base() << endl;
	}
		//LIST CHANNELS IN PARAMS
	if (!channels.empty())
	{
		for (vector<string>::const_iterator it = channels.begin(), ite = channels.end(); it != ite; it++)
		{
			vector<string> usersNames;
			map<string, bool> users;
			cout << *it.base() << endl;
			try
			{
				Channel &chan = _datasPtr->getChannel(*it.base());
				users = chan.getUsers();
				for (map<string, bool>::const_iterator itb = users.begin(), itbe = users.end(); itb != itbe; itb++)
				{
					if (chan.userIsActive(itb->first)) {
						if (itb->second)
							usersNames.insert(usersNames.begin(), "@" + _datasPtr->getUser(itb->first, USERNAME).getNickName());
						else
							usersNames.insert(usersNames.begin(), _datasPtr->getUser(itb->first, USERNAME).getNickName());
					}
				}
				list.insert(list.begin(), make_pair<string, vector<string> >(*it.base(), usersNames));
			}
			catch (datasException &e) {}
		}
	}
	else //LIST ALL CHANNELS
	{
		for (channelsDatas::const_iterator it = _datasPtr->getChannels().begin(),
			ite = _datasPtr->getChannels().end(); it != ite; it++)
		{
			vector<string> usersNames;
			map<string, bool> users;
			Channel *chan = it->second;
			try
			{
				users = it->second->getUsers();
				for (map<string, bool>::const_iterator itb = users.begin(), itbe = users.end(); itb != itbe; itb++)
				{
					if (chan->userIsActive(itb->first)) {
						if (itb->second)
							usersNames.insert(usersNames.begin(), "@" + _datasPtr->getUser(itb->first, USERNAME).getNickName());
						else
							usersNames.insert(usersNames.begin(), _datasPtr->getUser(itb->first, USERNAME).getNickName());
					}
				}
				list.insert(make_pair<string, vector<string> >(it->first, usersNames));
			}
			catch (datasException &e) {}
		}
	}

	//ADD USER WITHOUT CHANNELS IN LIST
	vector<string> usersNames;
	for (usersDatas::const_iterator it = _datasPtr->getUsers().begin(),
		ite = _datasPtr->getUsers().end(); it != ite; it++)
	{
		if (it->second->getChannels().empty())
			usersNames.insert(usersNames.begin(), it->second->getNickName());
	}
	if (!usersNames.empty())
		list.insert(make_pair<string, vector<string> >("*", usersNames));

	//PRINT LIST
	map<string, vector<string> >::const_iterator it = list.begin();
	for (map<string, vector<string> >::const_iterator ite = list.end(); it != ite; it++)
	{
		sendMsgToClient(_fd, "=" + it->first);
		stringstream msg;
		for (vector<string>::const_iterator vIt = it->second.begin(), vIte = it->second.end(); vIt != vIte; vIt++) {
			msg << *vIt.base();
			if (vIt + 1 != vIte)
				msg << " * ";
		}
		sendMsgToClient(_fd, msg.str()); // RPL_NAMEREPLY
	}
	sendMsgToClient(_fd, it->first + " :End of NAMES list");
	return(list);
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

void	User::kick(const string &nickName, const string &chanName)
{
	std::string	msg;
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
	_datasPtr->removeUserFromChannel(user.getUserName(), chanName);
	chan.responseCmdToAllInChan(*this, "KICK " + chanName + " " + nickName + " :no reason");
}

void	User::mode(const string &chanName, const int chanMode, const bool add)
{
	if (!chanName.empty() && chanName[0] != '#')
		return;

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
		throw datasException(_nickName + chanName + " :They aren't on that channel", 441); // ERR_USERNOTINCHANNEL
	}
	if (!chan.userIsChanOp(_userName))
		throw datasException(chanName + " :You're not channel operator", 482); // ERR_CHANOPRIVSNEEDED
	chan.setMod(chanMode, add);
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

	_datasPtr->sendMsgByServerToExecuter(*this, "341 " + nickName + " " + chanName);
	_datasPtr->responseToCmd(*this, "INVITE " + _nickName + " :" + chanName, _datasPtr->getUser(nickName, NICKNAME).getFd());
}

void	User::topic(const string &chanName, const string &newTopicName)
{
	_datasPtr->getChannel(chanName).getUser(_userName); // ERR_NOTONCHANNEL
	if (newTopicName.empty())
	{
		sendMsgToClient(_fd ,chanName + " :No topic is set"); // RPL_NOTOPIC
		return;
	}
	_datasPtr->newChannelTopic(_userName, chanName, newTopicName); // ERR_CHANOPRIVSNEEDED ERR_NOCHANMODES
	//sendMsgToChannel(chanName,chanName + " :" + newTopicName); // RPL_TOPIC
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
