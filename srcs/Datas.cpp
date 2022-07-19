#include "../includes/Datas.hpp"
#include "../includes/User.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Command.hpp"
#include "../includes/tester.hpp"

Datas::Datas(void): _cmd(Command()) {}

Datas::Datas(std::string& pwd): _pwd(pwd), _cmd(Command()) {}

Datas::~Datas()
{
	for (usersDatas_it it = _usersDatas.begin(); it != _usersDatas.end(); it++)
		delete it->second;
	for (channelsDatas_it it = _channelsDatas.begin(); it != _channelsDatas.end(); it++)
		delete it->second;
	_usersDatas.clear();
	_channelsDatas.clear();
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

User &Datas::getUser(const string &userName) const
{
	usersDatas_const_it	it = _usersDatas.begin();
	usersDatas_const_it	ite = _usersDatas.end();

	while (it != ite)
	{
		if (!it->second->getUserName().compare(userName))
			return (*it->second);
		it++;
	}
	throw datasException("User doesn't exist", userName);
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
	throw datasException("Channel doesn't exist", chanName);
}

const std::string &Datas::getPwd(void) const
{
	return (_pwd);
}

Command	&Datas::getCmd(void)
{
	return (_cmd);
}

// FUNCTIONS

void	Datas::disconnectUser(User& user)
{
	channelsDatas_it	it = _channelsDatas.begin();
	channelsDatas_it	ite = _channelsDatas.end();
	usersInChannel	itUsers;

	while (it != ite)
	{
		it->second->deleteUser(user.getUserName());
		it++;
	}
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
	size_t		posNL = lines.find_first_of("\n\r");
	size_t		posTmp;
	std::string	line = lines.substr(0, posNL);
	std::string	msg;

	if (it == usersData.end()) {
		newUser(fd);
	}
	while (line.length() && posNL != std::string::npos) {
		if (it->second->getStep() < 5)
			msg = it->second->fillUser(line);
		else if (!line.find_first_of("/"))
			it->second->execCmd(line.substr(1));
		else
			it->second->sendMsgToChannel(line);
		posTmp = posNL;
		posNL = lines.find_first_of("\n\r", posNL + 1);
		line = lines.substr(posTmp + 1, posNL - (posTmp + 1));
	}
	if (msg.length())
		sendMsgToClient(fd, msg);
}

void	Datas::sendPrompt(int fd)
{
	time_t	tmm = time(0);
	char*	dt = ctime(&tmm);

	send(fd, dt + 11, 8, 0);
	send(fd, " | ", 3, 0);
}

void	Datas::displayServLogo(int fd)
{
	cleanScreen(fd);
	sendMsgToClient(fd, SERVLOGO);
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
	if (chan.chanModeIs(MODE_I))
		chan.useInvit(userName);
	getChannel(chanName).addUser(userName, role);
	getUser(userName).addChannel(chanName, role);
}

void Datas::removeUserFromChannel(const string &userName, const string &chanName) {
	Channel &chan =  getChannel(chanName);
	User &user = getUser(userName);
	chan.deleteUser(userName);
	if (chan.getUsers().empty()) {
		delete &chan;
		_channelsDatas.erase(chanName);
	}
	user.deleteChannel(chanName);
}

void Datas::deleteChannel(const string chanName)
{
	if (_channelsDatas.erase(chanName) <= 0)
		throw datasException("Channel doesn't exist", chanName);
}

void Datas::newChannelTopic(const string userName, const string chanName, const string newChanName)
{
	try
	{
		getChannel(newChanName);
	} catch (datasException &e) {
		Channel &chan = getChannel(chanName);
		if (!chan.userIsChanOp(userName))
			throw datasException("Not operator in " + chanName, userName);
		if (!chan.chanModeIs(MODE_T))
			throw datasException("Channel not in +t mode", chanName);
		chan.setChanName(*this, newChanName);
		Channel *tmp = new Channel(chan);
		delete _channelsDatas.find(chanName)->second;
		_channelsDatas.erase(chanName);
		_channelsDatas.insert(make_pair<string, Channel *>(newChanName, tmp));
		return;
	}
	throw datasException("Channel name already used", chanName + " -> " + newChanName);
}

void Datas::clearCmd(void)
{
	_cmd.clearCmd();
}
