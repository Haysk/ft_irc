#include "../includes/Datas.hpp"
#include "../includes/User.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Command.hpp"
#include "../includes/tester.hpp"

Datas::Datas(void) {}

Datas::Datas(std::string& pwd): _pwd(pwd) {}

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

// FUNCTIONS

void	Datas::newUser(int fd) {
	User	*user;

	user = new User(fd);
	_usersDatas.insert(make_pair(fd, user));
}

void	Datas::treatCmds(int fd, string cmds)
{
	usersDatas		usersData = getUsers();
	usersDatas_const_it	it = usersData.find(fd);
	size_t		posNL = cmds.find_first_of("\n");
	size_t		posTmp;
	std::string	cmd = cmds.substr(0, posNL);
	std::string	msg;

	while (cmd.length() && posNL != std::string::npos) {
		if (it == usersData.end()) {
			sendMsgToClient(fd, "Welcome to my server IRCserv !");
			newUser(fd);
		}
		else if (it->second->getStep() < 5)
			msg = it->second->fillUser(*this, cmd);
		else if (!cmd.find_first_of("/"))
		{
			cmd = cmd.substr(1);
			it->second->execCmd(*this, cmd);
		}
		posTmp = posNL;
		posNL = cmds.find_first_of("\n", posNL + 1);
		cmd = cmds.substr(posTmp + 1, posNL - posTmp);
	}
	sendMsgToClient(fd, msg);
}

void Datas::newChannel(const string &chanName, const int mode, const string &userName)
{
	try {
		getChannel(chanName);
	} catch (datasException &e) {
		Channel *chan;
		chan = new Channel(chanName, mode, userName);
		_channelsDatas.insert(make_pair(chanName, chan));
		return;
	}
	throw datasException("Channel already exist", chanName);
}

void Datas::addUserInChannel(const string &userName, const string &chanName, bool role = false)
{
	getChannel(chanName).addUser(userName, role);
	getUser(userName).addChannel(chanName, role);
}

void Datas::removeUserFromChannel(const string &userName, const string &chanName) {
	Channel &chan =  getChannel(chanName);
	chan.deleteUser(userName);
	if (chan.getUsers().empty()) {
		delete &chan;
		_channelsDatas.erase(chanName);
	}
}

void Datas::deleteChannel(const string chanName)
{
	if (_channelsDatas.erase(chanName) <= 0)
		throw datasException("Channel doesn't exist", chanName);
}
