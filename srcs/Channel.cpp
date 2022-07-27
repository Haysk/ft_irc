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
	throw datasException(_chanName + " : You\'re not on that Channel", 442); // ERR_NOTONCHANNEL
}

bool Channel::userIsChanOp(const string &userName) const
{
	usersInChannel_const_it it;
	it = _users.find(userName);
	if (it != _users.end())
		return it->second;
	throw datasException(_chanName + " : You\'re not on that Channel", 442); // ERR_NOTONCHANNEL
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

void Channel::setTopic(const string &newTopic) {
	_topic = newTopic;
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
	try {
		getUser(userName);
		throw datasException(userName +  _chanName + " :is already on channel", 443); // ERR_USERONCHANNEL
	} catch (datasException &e) {
		for (vector<string>::iterator it = _invit.begin(), ite = _invit.end(); it != ite; it++)
			if (!it.base()->compare(userName))
				return;
		_invit.push_back(userName);
	}
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
		throw datasException(_chanName + " : You\'re not on that Channel", 442); // ERR_NOTONCHANNEL
}

void Channel::useInvit(const string &userName)
{
	for (vector<string>::iterator it = _invit.begin(), ite = _invit.end(); it != ite; it++)
		if (!it.base()->compare(userName))
		{
			_invit.erase(it);
			return;
		}
	throw (datasException(_chanName + " :Cannot join channel (+i)", 473)); // ERR_INVITEONLYCHAN
}

void Channel::responseJoinToUsersInChan(User& joiner)
{
	usersInChannel_it	it = _users.begin();
	usersInChannel_it	ite = _users.end();

	while (it != ite)
	{
		_datasPtr->responseToCmd(joiner, "JOIN :" + _chanName, "", _datasPtr->getUser(it->first, USERNAME).getFd());
		it++;
	}
}

void	Channel::sendModeChannel(User& user)
{
	string	msg = ":ircserv 324 " + user.getNickName() + " " + _chanName;
	switch (_mode)
	{
		case MODE_I:
			msg += " +i";
			break;
		case MODE_T:
			msg += " +t";
			break;
		case MODE_I | MODE_T:
			msg += " +it";
			break;
	}
	sendMsgToClient(user.getFd(), msg);
}

ostream& operator<<(ostream& os, const Channel& rhs) {
	os << "\n" << rhs.getChanName() << " :" << endl;
	const usersInChannel &users = rhs.getUsers();
	for (usersInChannel_const_it it = users.begin(); it != users.end(); it++)
		os << "\n\t\t" << it->first << "\n\t\trole : " << it->second << endl;
	return os;
}
