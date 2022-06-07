#include "Datas.h"
#include "User.h"
#include "Channel.h"

Datas::Datas() {}

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

const Datas::usersDatas &Datas::getUsers() const
{
	return _usersDatas;
}

const Datas::channelsDatas &Datas::getChannels() const
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
	throw datasException("User doesn't exist");
}

Channel &Datas::getChannel(const string &chanName) const
{
	channelsDatas_const_it it;

	it = _channelsDatas.find(chanName);
	if (it != _channelsDatas.end())
		return *it->second;
	throw datasException("Channel doesn't exist");
}

// FUNCTIONS

void Datas::newUser(const string &userName, const string &nickName, const string &ipAddress, int port)
{
	if (!_usersDatas.empty())
		getUser(userName);
	User *user;
	user = new User(userName, nickName, ipAddress, port);
	if (!_usersDatas.insert(make_pair(userName, user)).second)
		throw datasException("User already exist");
}

void Datas::newChannel(const string &chanName, const int mode, const string &userName)
{
	try {
		getChannel(chanName);
	} catch (exception &e) {
		Channel *chan;
		chan = new Channel(chanName, mode, userName);
		if (!_channelsDatas.insert(make_pair(chanName, chan)).second)
			throw datasException("Channel already exist");
	}
}

void Datas::addUserInChannel(const string &userName, const string &chanName, bool role = false)
{
	getChannel(chanName);
	getChannel(chanName).addUser(userName, role);
}

void Datas::removeUserFromChannel(const string &userName, const string &chanName) {
	getChannel(chanName).deleteUser(userName);
}

void Datas::deleteChannel(const string chanName)
{
	if (_channelsDatas.erase(chanName) <= 0)
		throw datasException("Channel doesn't exist");
}
