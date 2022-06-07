#include "Channel.h"
#include "User.h"

Channel::Channel() {}

Channel::Channel(const string &chanName, int mode, const string &userName) :
_chanName(chanName),
_mode(mode)
{
	addUser(userName, true);
}

Channel::~Channel()
{
	_users.clear();
}

Channel &Channel::operator=(const Channel &rhs)
{
	this->_chanName = rhs.getChanName();
	this->_mode = rhs.getMode();
	this->_users = rhs.getUsers();
	return *this;
}

// GETTERS

string Channel::getChanName() const
{
	return _chanName;
}

int Channel::getMode() const
{
	return _mode;
}

Channel::usersInChannel Channel::getUsers() const
{
	return _users;
}

User &Channel::getUser(const string &userName) const
{
	usersInChannel_const_it it;
	it = _users.find(userName);
	if (it != _users.end())
	{
		return Datas::getUser(it->first);
	}
	throw channelException("User not in this Channel");
}

bool Channel::userIsOperator(const string &userName) const {
	usersInChannel_const_it it;
	it = _users.find(userName);
	if (it != _users.end())
	{
		return it->second;
	}
	throw channelException("User not in this Channel");
}

// SETTERS

void Channel::setChanName(const string newName)
{
	_chanName = newName;
}

void Channel::setMod(int newMode)
{
	_mode = newMode;
}

// FUNCTIONS

void Channel::addUser(const string userName, bool role = false)
{
	try {
		getUser(userName);
	} catch (exception &e) {
		_users.insert(make_pair(userName, role));
	}
}

void Channel::deleteUser(const string userName)
{
	if (_users.erase(userName) <= 0)
		throw channelException("User not in This Channel");
}
