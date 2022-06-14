#include "../includes/Datas.hpp"
#include "../includes/User.hpp"
#include "../includes/Channel.hpp"
#include "../includes/PreUser.hpp"

Datas::Datas(void) {}

Datas::Datas(std::string& pwd): _pwd(pwd) {}

Datas::~Datas()
{
	for (usersDatas_it it = _usersDatas.begin(); it != _usersDatas.end(); it++)
		delete it->second;
	for (channelsDatas_it it = _channelsDatas.begin(); it != _channelsDatas.end(); it++)
		delete it->second;
	for (preUsers_it it = _preUsers.begin(); it != _preUsers.end(); it++)
		delete it->second;
	_usersDatas.clear();
	_channelsDatas.clear();
//	_preUsers.clear();
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
	usersDatas_const_it it;

	it = _usersDatas.find(userName);
	if (it != _usersDatas.end()) {
		return *it->second;
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

void Datas::newUser(const string &userName, const string &nickName, const string &ipAddress, int port)
{
	try {
		getUser(userName);
	} catch (datasException &e) {
		User *user;
		user = new User(userName, nickName, ipAddress, port);
		_usersDatas.insert(make_pair(userName, user));
		return;
	}
	throw datasException("User already exist", userName);
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

void Datas::newPreUser(int fd)
{
	try {
		//This function need to be declare
		// getPreUser(fd);
	} catch (datasException &e) {
		PreUser *preUser;
		preUser = new PreUser(fd);
		// _usersDatas.insert(make_pair(fd, preUser));
		return;
	}
	// Need to be declare
	// throw datasException("PreUser already exist", fd);
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
