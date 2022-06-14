#include "../includes/User.hpp"

User::User() {}

User::User(const string &userName, const string &nickName, const string &ipAddress, int port) :
_userName(userName),
_nickName(nickName),
_ipAddress(ipAddress),
_port(port)
{
}
User::~User()
{
	_channels.clear();
}

User &User::operator=(const User &rhs)
{
	_userName = rhs.getUserName();
	_nickName = rhs.getNickName();
	_ipAddress = rhs.getIpAddress();
	_port = rhs.getPort();
	_channels = rhs.getChannels();
	return *this;
}

// GETTERS

const string &User::getUserName() const
{
	return _userName;
}

const string &User::getNickName() const
{
	return _nickName;
}

const string &User::getIpAddress() const
{
	return _ipAddress;
}

const int &User::getPort() const
{
	return _port;
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

// SETTERS

void User::setNickName(const string &nickName)
{
	_nickName = nickName;
}

void User::setIpAddress(const string &ipAddress)
{
	_ipAddress = ipAddress;
}

void User::setPort(const int &port)
{
	_port = port;
}

// UTILS

void User::addChannel(const string &chanName, bool role) {
	if (_channels.insert(make_pair(chanName, role)).second == false)
		throw datasException("User aleady in " + chanName , _userName);

}

// FUNCTIONS

void User::createChannel(Datas &datas, const string &chanName, const int mode)
{
	datas.newChannel(chanName, mode, _userName);
	_channels.insert(make_pair(chanName, true));
}

void User::joinChannel(Datas &datas, const string &chanName)
{
	datas.addUserInChannel(_userName, chanName, false);
}

void User::quitChannel(Datas &datas, const string &chanName)
{
	if (_channels.erase(chanName) > 0)
		datas.removeUserFromChannel(_userName, chanName);
	else
		throw datasException("User not in this Channel", _userName);
}

ostream& operator<<(ostream& os, const User& rhs)
{
	os << "\n" << rhs.getUserName() << ":\n\tNick Name : " << rhs.getNickName()
	<< "\n\tIp Address : " << rhs.getIpAddress() << "\n\tPort : " << rhs.getPort();
	os << "\n\tChannels :\n";
	const userChannels &channels = rhs.getChannels();
	for (userChannels_const_it it = channels.begin(); it != channels.end(); it++)
		os << "\n\t\t" << it->first << "\n\t\trole : " << it->second << endl;
	return os;
}
