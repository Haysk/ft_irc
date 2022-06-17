#include "../includes/User.hpp"

User::User(): _step(1) {}

User::~User()
{
	_channels.clear();
}

User &User::operator=(const User &rhs)
{
	_userName = rhs.getUserName();
	_nickName = rhs.getNickName();
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

void User::setUserName(const usersDatas &users, const string &userName)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();

	while (it != ite)
	{
		if (!it->second->getUserName().compare(userName))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_userName = userName;
	std::cout << "Well " << _userName << ", now enter your nickname: " << std::endl;
}

void User::setNickName(const usersDatas &users, const string &nickName)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();

	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickName))
			throw std::invalid_argument("The username passed is already assigned");
		it++;
	}
	_nickName = nickName;
}

// UTILS

void	User::checkPwd(const std::string pwd, std::string arg) {
	if (pwd.compare(arg)) {
		throw std::invalid_argument("The password passed isn't valid");
	}
	std::cout << "Great !! Now enter your username: " << std::endl;
}

void	User::addChannel(const string &chanName, bool role) {
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
			setUserName(servDatas.getUsers(), arg);
			break;
		case 3:
			setNickName(servDatas.getUsers(), arg);
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

void	User::createChannel(Datas &datas, const string &chanName, const int mode)
{
	datas.newChannel(chanName, mode, _userName);
	_channels.insert(make_pair(chanName, true));
}

void	User::joinChannel(Datas &datas, const string &chanName)
{
	datas.addUserInChannel(_userName, chanName, false);
}

void	User::quitChannel(Datas &datas, const string &chanName)
{
	if (_channels.erase(chanName) > 0)
		datas.removeUserFromChannel(_userName, chanName);
	else
		throw datasException("User not in this Channel", _userName);
}

ostream&	operator<<(ostream& os, const User& rhs)
{
	os << "\n" << rhs.getUserName() << ":\n\tNick Name : " << rhs.getNickName();
	os << "\n\tChannels :\n";
	const userChannels &channels = rhs.getChannels();
	for (userChannels_const_it it = channels.begin(); it != channels.end(); it++)
		os << "\n\t\t" << it->first << "\n\t\trole : " << it->second << endl;
	return (os);
}
