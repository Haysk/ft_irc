#include "../includes/User.hpp"
#include "../includes/Channel.hpp"

User::User(Datas *datasPtr, int fd): _datasPtr(datasPtr), _fd(fd), _step(1) {}

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

const int &User::getFd() const
{
	return _fd;
}

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

void User::setUserName(const string &userName)
{
	// usersDatas_const_it	it = users.begin();
	// usersDatas_const_it	ite = users.end();

	// while (it != ite)
	// {
	// 	if (!it->second->getUserName().compare(userName))
	// 		throw std::invalid_argument("The nickname passed is already assigned");
	// 	it++;
	// }
	// _userName = userName;
	// sendMsgToClient(_fd, "Well " + _userName + ", now enter your nickname: ");
	try {
		_datasPtr->getUser(userName);
		throw std::invalid_argument("The username passed is already assigned");
	} catch (datasException &e) {
		_userName = userName;
		sendMsgToClient(_fd, "Well " + _userName + ", now enter your nickname: ");
	}


}

void User::setNickName(const string &nickName)
{
	usersDatas_const_it	it = _datasPtr->getUsers().begin();
	usersDatas_const_it	ite = _datasPtr->getUsers().end();

	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickName))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_nickName = nickName;
}

// UTILS

void	User::checkPwd(const string arg) {
	if (_datasPtr->getPwd().compare(arg)) {
		throw std::invalid_argument("The password passed isn't valid");
	}
	sendMsgToClient(_fd, "Great !! Now enter your username");
}

void	User::addChannel(const string &chanName, bool role) {
	if (_channels.insert(make_pair(chanName, role)).second == false)
		throw datasException("User already in " + chanName , _userName);
}

// FUNCTIONS

void	User::fillUser(const string arg) {
	switch (_step) {
		case 1:
			checkPwd(arg);
			break;
		case 2:
			setUserName(arg);
			break;
		case 3:
			setNickName(arg);
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
}

void	User::execCmd(std::string cmd)
{
	Command	command(cmd);

	command.checkCmd(*_datasPtr, *this);
	std::cout << "EXECUTION: " + cmd + " by " + _userName << std::endl;
	sendMsgToClient(_fd, "EXECUTION: " + cmd + " by " + _userName);
}

void	User::createChannel(const string &chanName, const int mode)
{
	_datasPtr->newChannel(chanName, mode, _userName);
	_channels.insert(make_pair(chanName, true));
}

void	User::joinChannel(const string &chanName)
{
	_datasPtr->addUserInChannel(_userName, chanName, false);
}

void	User::quitChannel(const string &chanName)
{
	_datasPtr->removeUserFromChannel(_userName, chanName);
}

void	User::deleteChannel(const string &chanName)
{
	if (_channels.erase(chanName) <= 0)
		throw datasException("User not in this Channel", _userName);
}

// OPERATOR FUNCTION

void	User::kick(const string &userName, const string &chanName)
{
	if (!_datasPtr->getChannel(chanName).userIsOperator(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	_datasPtr->removeUserFromChannel(userName, chanName);
}

void	User::mode(const string &chanName, const int chanMode, const bool add) {
	Channel &chan = _datasPtr->getChannel(chanName);
	if (!chan.userIsOperator(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	chan.setMod(chanMode, add);
}

void	User::invite(const string &userName, const string &chanName) {
	Channel &chan = _datasPtr->getChannel(chanName);
	if (!chan.userIsOperator(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	if (!chan.chanModeIs(MODE_I))
		throw (datasException("Channel need to be in +i mode", chanName));
	_datasPtr->getUser(userName);
	chan.setInvit(userName);
	//envoyer un message au client;
	

}

void	User::topic(const string &chanName, const string &newChanName)
{
	_datasPtr->newChannelTopic(_userName, chanName, newChanName);
}

ostream&	operator<<(ostream& os, const User& rhs)
{
	os << "\n" << rhs.getUserName() << ":\n\tNick Name : \t" << rhs.getNickName();
	os << "\n\tChannels :\n";
	const userChannels &channels = rhs.getChannels();
	for (userChannels_const_it it = channels.begin(); it != channels.end(); it++)
		os << "\t\t\t" << it->first << "\n\t\t\trole : " << it->second << endl << endl;
	return (os);
}
