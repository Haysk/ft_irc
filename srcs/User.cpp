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

std::string	User::initUserName(string &userCmd)
{
	std::string	name;

	checkCmdName(userCmd, "USER");
	checkUserCmdNbrArg(userCmd, " ");
	name = getArgAt(userCmd, 1, " ");
	checkLenArg(name, 9);
	_hostName = getArgAt(userCmd, 2, " ");
	_serverName = getArgAt(userCmd, 3, " ");
	_realName = getRealName(userCmd);
	try
	{
		_datasPtr->getUser(name, USERNAME);
		throw std::invalid_argument("The name passed is already assigned");
	}
	catch (datasException &e)
	{
		for (map<string, string>::const_iterator it = _datasPtr->getOperatorConf().begin(), ite = _datasPtr->getOperatorConf().end();
				it != ite; it++)
		{
			if (it->second == _password && it->first == name)
			{
				_userName = name;
				_op = true;
				return ("Great ! You are now Operator");
			}
		}
		if (_password != _datasPtr->getPwd())
			throw datasException("Operator registration has failed");
		_userName = name;
	}
	return ("Great ! You are now registered\nTo see all the availables commands, enter: /show");
}

std::string	User::initNickName(const usersDatas &users, string &nickCmd)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();
	std::string	nickname;

	checkCmdName(nickCmd, "NICK");
	checkRangeArg(nickCmd, 2, 2);
	nickname = getArgAt(nickCmd, 1, " ");
	checkLenArg(nickname, 9);
	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickname))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_nickName = nickname;
	return ("Well " + _nickName + ", now enter your username:");
}

// UTILS

std::string	User::checkCAPLS(std::string &arg)
{
	if (arg.find("CAP ") != 0 || getArgAt(arg, 1, " ").find("LS") != 0)
		throw std::invalid_argument("You've to send us: CAP LS");
	return ("In order to register on our Ircserv, enter the commands in sequence\n1) PASS <password>\n2) NICK <nickname>\n3) USER <username> <host> <server> <:realname>");
}

std::string	User::checkPwd(const std::string pwd, std::string &pwdLine)
{
	std::string	pwdSent;

	checkCmdName(pwdLine, "PASS");
	checkNbrArg(pwdLine, 2);
	pwdSent = getArgAt(pwdLine, 1, " ");
	for (map<string, string>::const_iterator it = _datasPtr->getOperatorConf().begin(), ite = _datasPtr->getOperatorConf().end();
			it != ite; it++)
	{
		if (!it->second.compare(pwdSent))
		{
			_password = pwdSent;
			return ("Hi new operator !! Now enter your nickname or try another password:");
		}
	}
	if (pwdSent.compare(0, strlenP(pwdSent), pwd))
		return ("The password passed isn't valid\nNow enter your nickname or try another password:");
    _password = pwdSent;
	return ("Hi new user !! Now enter your nickname or try another password:");
}

void	User::addChannel(const string &chanName, bool role) {
	if (!_channels.insert(make_pair(chanName, role)).second)
		throw datasException("User already in " + chanName , _userName);
}

// FUNCTIONS

const string	User::fillUser(string &arg) {
	string	msg;
	string	cmd = getArgAt(arg, 0, " ");

	if (!cmd.compare("PASS") && _step == 3)
		_step--;
	switch (_step) {
		case 1:
			msg = checkCAPLS(arg);
			break;
		case 2:
			msg = checkPwd(_datasPtr->getPwd(), arg);
			break;
		case 3:
			msg = initNickName(_datasPtr->getUsers(), arg);
			break;
		case 4:
			try {
				msg = initUserName(arg);
			} catch (datasException &e) {
				sendMsgToClient(_fd, "ERROR: " + string(e.what()));
				_step--;
			}
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
	return (msg);
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

void	User::sendMsgToChannel(const std::string& chanName, const std::string& msg)
{
	User	user;
	usersDatas	users;
	usersDatas_it	it;
	usersDatas_it	ite;

	if (!_activeChannel.length())
		throw std::invalid_argument("Invalid input");
	users = _datasPtr->getUsers();
	it = users.begin();
	ite = users.end();
	while (it != ite)
	{
		user = *it->second;
		if (!user.getActiveChannel().compare(chanName)
				&& user.getUserName().compare(_userName))
			sendMsgToClientInChan(_nickName, it->first, msg);
		it++;
	}
}

void	User::join(const string &chanName)
{
	try {
		createChannel(chanName, 0);
		_activeChannel = chanName;
		_datasPtr->getChannel(chanName).displayInterface(_fd);
		sendMsgToChannel(chanName, "JOINED THE CHANNEL");
	} catch (datasException &e) {
		try {
			_datasPtr->getChannel(chanName).getUser(_userName);
			if (_activeChannel != chanName) {
				_activeChannel = chanName;
				_datasPtr->getChannel(chanName).displayInterface(_fd);
				sendMsgToChannel(chanName, "JOINED THE CHANNEL");
			}
		} catch (datasException &e) {
			if (_op)
				_datasPtr->addUserInChannel(_userName, chanName, true);
			else
				_datasPtr->addUserInChannel(_userName, chanName, false);
			_activeChannel = chanName;
			_datasPtr->getChannel(chanName).displayInterface(_fd);
			sendMsgToChannel(chanName, "JOINED THE CHANNEL");
		}
	}
}

void	User::part(const string &chanName)
{
	_datasPtr->displayServLogo(_fd);
	_datasPtr->removeUserFromChannel(_userName, chanName);
}

void	User::quit(const std::string& msg)
{
	(void)msg;
	_co = false;
//	if (msg.length())
//		sendToAll(msg);
}

void	User::deleteChannel(const string &chanName)
{
	if (_channels.erase(chanName) <= 0)
		throw datasException("User not in this Channel", _userName);
	if (chanName == _activeChannel)
		_activeChannel = "";

}

void User::sendPrivateMessage(const string &destName, const string &message) {
	User &dest = _datasPtr->getUser(destName, NICKNAME);
	sendMsgToClient(dest.getFd(), "PRIVATE : " + message);
}

map<string, vector<string> > User::names(const vector<string> &channels)
{
	map<string, vector<string> > list;

	//LIST CHANNELS IN PARAMS
	if (!channels.empty())
	{
		for (vector<string>::const_iterator it = channels.begin(), ite = channels.end(); it != ite; it++)
		{
			vector<string> usersNames;
			map<string, bool> users;
			try
			{
				Channel &chan = _datasPtr->getChannel(*it.base());
				users = chan.getUsers();
				for (map<string, bool>::const_iterator it = users.begin(), ite = users.end(); it != ite; it++)
				{
					if (chan.userIsActive(it->first)) {
						if (it->second)
							usersNames.insert(usersNames.begin(), "@" + _datasPtr->getUser(it->first, USERNAME).getNickName());
						else
							usersNames.insert(usersNames.begin(), _datasPtr->getUser(it->first, USERNAME).getNickName());
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
				for (map<string, bool>::const_iterator it = users.begin(), ite = users.end(); it != ite; it++)
				{
					if (chan->userIsActive(it->first)) {
						if (it->second)
							usersNames.insert(usersNames.begin(), "@" + _datasPtr->getUser(it->first, USERNAME).getNickName());
						else
							usersNames.insert(usersNames.begin(), _datasPtr->getUser(it->first, USERNAME).getNickName());
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
			usersNames.insert(usersNames.begin(), it->second->getUserName());
	}
	if (!usersNames.empty())
		list.insert(make_pair<string, vector<string> >("*", usersNames));

	//PRINT LIST
	for (map<string, vector<string> >::const_iterator it = list.begin(), ite = list.end(); it != ite; it++)
	{
		sendMsgToClient(_fd, it->first);
		for (vector<string>::const_iterator vIt = it->second.begin(), vIte = it->second.end(); vIt != vIte; vIt++) {
			string msg;
			msg = "\t" + *vIt.base();
			sendMsgToClient(_fd, msg);
		}
	}
	return(list);
}

// CHAN OPERATOR FUNCTION

void	User::kick(const string &nickName, const string &chanName)
{
	std::string	msg;

	if (!_datasPtr->getChannel(chanName).userIsChanOp(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	_datasPtr->removeUserFromChannel(nickName, chanName);
	_datasPtr->updateKickedInterface(_datasPtr->getUser(nickName, NICKNAME),
			chanName);
	msg = "KICK " + nickName + " FROM THIS CHANNEL";
	sendMsgToChannel(chanName, msg);
}

void	User::mode(const string &chanName, const int chanMode, const bool add) {
	Channel	&chan = _datasPtr->getChannel(chanName);

	if (!chan.userIsChanOp(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	sendMsgToChannel(chanName, getMsgMode(chanMode, add));
	chan.setMod(chanMode, add);
}

void	User::invite(const string &userName, const string &chanName) {
	try {
		_datasPtr->getChannel(chanName);
	} catch (datasException &e) {
		_datasPtr->getUser(userName, USERNAME);
		//envoyer un message au client;
		return;
	}
	Channel &chan = _datasPtr->getChannel(chanName);
	if (chan.chanModeIs(MODE_I) && !chan.userIsChanOp(_userName))
		throw datasException("Channel " + chanName + " is in invite mode, you must be an operator", _userName);
	_datasPtr->getUser(userName, USERNAME);
	chan.setInvit(userName);
	//envoyer un message au client;
}

void	User::topic(const string &chanName, const string &newTopic)
{
	_datasPtr->newChannelTopic(_userName, chanName, newTopic);
	sendMsgToChannel(chanName,"CHANGE THE TOPIC BY " + newTopic );
}

ostream&	operator<<(ostream& os, const User& rhs)
{
	os << "\n" << rhs.getUserName() << ":\n\tNick Name : \t" << rhs.getNickName();
	os << "\n\tChannels :\n";
	const userChannels &channels = rhs.getChannels();
	for (userChannels_const_it it = channels.begin(); it != channels.end(); it++)
		os << "\t\t\t" << it->first << "\n\t\t\trole : " << it->second << endl << endl;
	return (os);
}
