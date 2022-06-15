#include "../includes/User.hpp"

User::User(): _step(1) {}

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

const int &User::getStep() const
{
	return _step;
}

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

void User::setUserName(usersDatas2 &users, const string &userName)
{
	usersDatas_it2	it = users.begin();
	usersDatas_it2	ite = users.end();

	while (it != ite)
	{
		if (!it->second->getUserName().compare(userName))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_userName = userName;
	std::cout << "Well " << _userName << ", now enter your nickname: " << std::endl;
}

void User::setNickName(usersDatas2 &users, const string &nickName)
{
	usersDatas_it2	it = users.begin();
	usersDatas_it2	ite = users.end();

	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickName))
			throw std::invalid_argument("The username passed is already assigned");
		it++;
	}
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

void	User::checkPwd(const std::string pwd, std::string arg) {
	if (pwd.compare(arg)) {
		throw std::invalid_argument("The password passed isn't valid");
	}
	std::cout << "Great !! Now enter your username: " << std::endl;
}

void User::addChannel(const string &chanName, bool role) {
	if (_channels.insert(make_pair(chanName, role)).second == false)
		throw datasException("User aleady in " + chanName , _userName);
}

// FUNCTIONS

void	User::fillUser(Datas &servDatas, std::string arg) {
	switch (_step) {
		case 1:
			checkPwd(servDatas.getPwd(), arg);
			break;
		case 2:
			setUserName(servDatas.getUsers2(), arg);
			break;
		case 3:
			setNickName(servDatas.getUsers2(), arg);
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
}

void	User::execCmd(Datas &servDatas, std::string cmd)
{
	Command	command(cmd);

	command.checkCmd(servDatas, *this);
	std::cout << "EXECUTION: " << cmd << " by " << getUserName() << std::endl;
}

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
