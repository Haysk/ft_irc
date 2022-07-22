#include "../includes/Channel.hpp"
#include "../includes/User.hpp"

Channel::Channel() {}

Channel::Channel(Datas *datasPtr, const string &chanName, int mode, const string &userName) :
_datasPtr(datasPtr),
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

bool Channel::chanModeIs(const int mode) const
{
	switch (mode) {
	case MODE_I :
		return ((_mode & MODE_I) >> BITWISE_I);
	case MODE_T :
		return ((_mode & MODE_T) >> BITWISE_T);
	case (MODE_I | MODE_T) :
		return ((_mode & MODE_I) >> BITWISE_I) & ((_mode & MODE_T) >> BITWISE_T);
	default :
		throw datasException("Mode doesn't exist", mode);
	}
}

usersInChannel Channel::getUsers() const
{
	return _users;
}

User &Channel::getUser(const string &userName) const
{
	usersInChannel_const_it it;

	it = _users.find(userName);
	if (it != _users.end())
		return _datasPtr->getUser(it->first, USERNAME);
	throw datasException("User not in this Channel");
}

bool Channel::userIsChanOp(const string &userName) const
{
	usersInChannel_const_it it;
	it = _users.find(userName);
	if (it != _users.end())
		return it->second;
	throw datasException("User not in this Channel", userName);
}

bool Channel::userIsActive(const string &userName)
{
	return (_datasPtr->getUser(userName, USERNAME).getActiveChannel() == _chanName);
}

Datas*	Channel::getDatasPtr(void)
{
	return (_datasPtr);
}

// SETTERS

void Channel::setChanName(const Datas &datas, const string &newName)
{
	usersInChannel_const_it it = _users.begin();
	usersInChannel_const_it ite = _users.end();
	for (;it != ite; it++)
	{
		User &user = datas.getUser(it->first, USERNAME);
		bool tmp = user.getChannels().find(_chanName)->second;
		user.deleteChannel(_chanName);
		user.addChannel(newName, tmp);
	}	
	_chanName = newName;
}

void Channel::setMod(const int newMode, const bool add)
{
	if (add)
		_mode = _mode | newMode;
	else
		_mode = _mode & ~newMode;
}

void Channel::setInvit(const string &userName)
{
	for (vector<string>::iterator it = _invit.begin(), ite = _invit.end(); it != ite; it++)
		if (!it.base()->compare(userName))
			throw (datasException("User already invited in " + _chanName, userName));
	_invit.push_back(userName);
}

// FUNCTIONS

void Channel::addUser(const string &userName, bool role = false)
{
	try {
		getUser(userName);
	} catch (exception &e) {
		_users.insert(make_pair(userName, role));
	}
}

void Channel::deleteUser(const string &userName)
{
	if (_users.erase(userName) <= 0)
		throw datasException("User not in This Channel");
}

void Channel::useInvit(const string &userName)
{
	for (vector<string>::iterator it = _invit.begin(), ite = _invit.end(); it != ite; it++)
		if (!it.base()->compare(userName))
		{
			_invit.erase(it);
			return;
		}
	throw (datasException("User " + userName + " is not invited in this channel", _chanName));
}

void	Channel::displayInterface(const int& fd)
{
	std::string	msg;
	usersInChannel_const_it it = _users.begin();
	usersInChannel_const_it ite = _users.end();

	cleanScreen(fd);
	msg = "\n--> You have joined the channel #";
	msg += _chanName;
	msg += "\n*** The topic is <<To build>>";
	msg += "\n*** The members are : ";
	while (it != ite)
	{
		if (it->second)
			msg += "@";
		msg += _datasPtr->getUser(it->first, USERNAME).getNickName();
		if (++it != _users.end())
			msg += " ; ";
	}
	msg += "\n---------------------------------------------";
	sendMsgToClient(fd, msg);
}

ostream& operator<<(ostream& os, const Channel& rhs) {
	os << "\n" << rhs.getChanName() << " :" << endl;
	const usersInChannel &users = rhs.getUsers();
	for (usersInChannel_const_it it = users.begin(); it != users.end(); it++)
		os << "\n\t\t" << it->first << "\n\t\trole : " << it->second << endl;
	return os;
}
