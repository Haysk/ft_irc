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

// FUNCTIONS

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

void	Datas::treatCmd(int fd, string cmd)
{
	usersDatas		usersData = getUsers();
	usersDatas_const_it	it = usersData.find(fd);

	if (it == usersData.end()){
		sendMsgToClient(fd, "Welcome to my server, please enter the password");
		newUser(fd);
	}
	else if (it->second->getStep() < 4)
		it->second->fillUser(cmd);
	else
		it->second->execCmd(cmd);
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
		if (!chan.userIsOperator(userName))
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
