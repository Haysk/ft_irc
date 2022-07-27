#include "../includes/Datas.hpp"
#include "../includes/User.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Command.hpp"
#include "../includes/tester.hpp"

Datas::Datas(): _cmd(Command()) {
	_operatorConf = getOperatorsConf();
}

Datas::Datas(std::string& pwd): _pwd(pwd), _cmd(Command()) {
	_co = true;
	_operatorConf = getOperatorsConf();
}

Datas::~Datas()
{
	for (usersDatas_it it = _usersDatas.begin(); it != _usersDatas.end(); it++)
		delete it->second;
	for (channelsDatas_it it = _channelsDatas.begin(); it != _channelsDatas.end(); it++)
		delete it->second;
	_usersDatas.clear();
	_channelsDatas.clear();
	_operatorConf.clear();
}

Datas &Datas::operator=(const Datas &rhs)
{
	this->_usersDatas = rhs.getUsers();
	this->_channelsDatas = rhs.getChannels();
	return *this;
}

// GETTERS

usersDatas &Datas::getUsers()
{
	return _usersDatas;
}

const usersDatas &Datas::getUsers() const
{
	return _usersDatas;
}

const channelsDatas &Datas::getChannels() const
{
	return _channelsDatas;
}

User &Datas::getUser(const string &name, bool config) const
{
	usersDatas_const_it	it = _usersDatas.begin();
	usersDatas_const_it	ite = _usersDatas.end();
	const std::string&	(User::*fct) () const;
	std::string	nameChecked;

	if (config)
		fct = &User::getNickName;
	else
		fct = &User::getUserName;
	while (it != ite)
	{
		nameChecked = (it->second->*fct) ();
		if (!nameChecked.compare(name))
			return (*it->second);
		it++;
	}
	if (config)
		throw datasException(name + " :No such nick/channel", 401); // ERR_NOSUCHNICK
	throw datasException("User doesn't exist", name);
}

User &Datas::getUser(int fd) const
{
	usersDatas_const_it	it = _usersDatas.begin();
	usersDatas_const_it	ite = _usersDatas.end();

	while (it != ite)
	{
		if (it->first == fd)
			return (*it->second);
		it++;
	}
	throw datasException("User fd doesn't exist", fd);
	
}

Channel &Datas::getChannel(const string &chanName) const
{
	channelsDatas_const_it it;

	it = _channelsDatas.find(chanName);
	if (it != _channelsDatas.end())
		return *it->second;
	throw datasException(chanName + " :No such channel", 403); // ERR_NOSUCHCHANNEL
}

const map<string, string> &Datas::getOperatorConf() const
{
	return _operatorConf;
}

const std::string &Datas::getPwd(void) const
{
	return (_pwd);
}

Command	&Datas::getCmd(void)
{
	return (_cmd);
}

bool	Datas::getCo(void) const
{
	return (_co);
}

// FUNCTIONS

void	Datas::disconnectUser(User& user)
{
	channelsDatas_it	it = _channelsDatas.begin();
	channelsDatas_it	ite = _channelsDatas.end();

	while (it != ite)
	{
		try
		{
			it->second->deleteUser(user.getUserName());
		}
		catch (datasException& e)
		{
		}
		it++;
	}
	_usersDatas.erase(user.getFd());
	delete &user;
}

void	Datas::newUser(int fd) {
	try {
		getUser(fd);
	} catch (datasException &e) {
		User	*user;

		user = new User(this, fd);
		_usersDatas.insert(make_pair(fd, user));
		return;
	}
		throw datasException("Fd already connected", fd);
}

void	Datas::treatCmds(int fd, string lines)
{
	usersDatas		usersData = getUsers();
	usersDatas_const_it	it = usersData.find(fd);
	size_t		start = 0;
	size_t		end = lines.find_first_of("\n\r");
	std::string	line = lines.substr(start, end);

	if (it == usersData.end()) {
		newUser(fd);
	}
	while (line.length() && start != std::string::npos) {
		std::cout << "CMD: " << line << std::endl;
		if (it->second->getStep() < 5)
			it->second->fillUser(line);
		else
			it->second->execCmd(line);
		start = lines.find_first_not_of("\n\r", end);
		end = lines.find_first_of("\n\r", start);
		if (start == std::string::npos)
			break;
		line = lines.substr(start, end - start);
	}
}

void	Datas::displayServLogo(int fd)
{
	vector<string>	logo = explode(SERVLOGO, '\n');
	size_t	vecSize = logo.size();
	size_t	i = 0;
	while (--vecSize)
	{
		sendMsgToClient(fd, logo[i]);
		i++;
	}
}

void Datas::newChannel(const string &chanName, const int mode, const string &userName)
{
	try {
		getChannel(chanName);
	} catch (datasException &e) {
		Channel *chan;
		chan = new Channel(this, chanName, mode, userName);
		_channelsDatas.insert(make_pair(chanName, chan));
		return;
	}
	throw datasException("Channel already exist", chanName);
}

void Datas::addUserInChannel(const string &userName, const string &chanName, bool role = false)
{
	Channel &chan = getChannel(chanName);
	cout << chan.getMode() << endl;
	if (chan.chanModeIs(MODE_I))
		chan.useInvit(userName);
	getChannel(chanName).addUser(userName, role);
	getUser(userName, USERNAME).addChannel(chanName, role);
}

void Datas::removeUserFromChannel(const string &userName, const string &chanName) {
	Channel &chan =  getChannel(chanName);
	User &user = getUser(userName, USERNAME);
	chan.deleteUser(user.getUserName());
	if (chan.getUsers().empty()) {
		delete &chan;
		_channelsDatas.erase(chanName);
	}
	user.deleteChannel(chanName);
}

void	Datas::updateKickedInterface(User& user, const std::string& chanName)
{
	std::string	msg;

	displayServLogo(user.getFd());
	msg = "You've been kicked from ";
	msg += chanName;
	sendMsgToClient(user.getFd(), msg);
}

void Datas::deleteChannel(const string chanName)
{
	if (_channelsDatas.erase(chanName) <= 0)
		throw datasException("Channel doesn't exist", chanName);
}

void Datas::newChannelTopic(const string userName, const string chanName, const string newTopicName)
{
	Channel &chan = getChannel(chanName);
	if (!chan.userIsChanOp(userName))
		throw datasException(chanName + " :You're not channel operator", 482); // ERR_CHANOPRIVSNEEDED
	if (!chan.chanModeIs(MODE_T))
		throw datasException(chanName + " :Channel doesn't support modes", 477); // ERR_NOCHANMODE
	chan.setTopic(newTopicName);
	return;
}

void Datas::clearCmd(void)
{
	_cmd.clearCmd();
}

void Datas::disconnectAllUsers(const string& comment)
{
	usersDatas_it	it = _usersDatas.begin();
	usersDatas_it	ite = _usersDatas.end();

	while (it != ite)
	{
		sendMsgToClient(it->first, "SERVER SHUTTING DOWN: " + comment);
		std::cout << BOLDRED << "client fd " << it->first << ": disconnected"<< RESET << std::endl;
		close(it->first);
		it++;
	}
	_co = false;
}

void Datas::responseToCmd(User& user, const string& cmdLine, const string& prevNickName, int fd)
{
	size_t	cmdLen = cmdLine.length();
	char	buf[cmdLen + 25];
	size_t	i = 0;
	string	msg = ":";

	if (prevNickName.length())
		msg += prevNickName;
	else
		msg += user.getNickName();
	msg += "!~" + user.getUserName();
	msg += "@localhost ";
	msg += cmdLine;
	cmdLen = msg.length();
	std::cout << "RESPONSETOCMD: ";
	while (i < cmdLen)
	{
		buf[i] = msg[i];
		std::cout << buf[i];
		i++;
	}
	buf[i++] = '\n';
	std::cout << std::endl;
	if (fd)
		send(fd, buf, i, 0);
	else
		send(user.getFd(), buf, i, 0);
}

void Datas::sendJoinMsgs(User& user, Channel& chan)
{
	chan.responseJoinToUsersInChan(user);
	responseChanNamesList(user, chan);
}

string Datas::getChanNamesListMsg(User& user, Channel& chan)
{
	string	msg = ":MyIrc 353 ";
	usersInChannel	users = chan.getUsers();
	usersInChannel_it	it = users.begin();
	usersInChannel_it	ite = users.end();
	User	tmp;

	msg += user.getNickName();
	msg += " = ";
	msg += chan.getChanName();
	msg += " :";
	while (it != ite)
	{
		tmp = getUser(it->first, USERNAME);
		if (it->second)
			msg += "@";
		msg += tmp.getNickName();
		if (it++ != ite)
			msg += " ";
	}
	return (msg);
}

string Datas::getChanNamesEndMsg(const string& nickName, const string& chanName)
{
	string	msg = ":MyIrc 366 ";
	
	msg += nickName;
	msg += " ";
	msg += chanName;
	msg += " :End of NAMES list.";
	return (msg);
}

void Datas::responseChanNamesList(User& user, Channel& chan)
{
	string	msg = getChanNamesListMsg(user, chan) + string("\n")
			+ getChanNamesEndMsg(user.getNickName(), chan.getChanName());
	char	buf[msg.length() + 1];
	size_t	i = 0;

	std::cout << "CHAN_NAMES_LIST_MSG: " << msg << std::endl;
	while (i < msg.length())
	{
		buf[i] = msg[i];
		i++;
	}
	buf[i++] = '\n';
	send(user.getFd(), buf, i, 0);
}
