#include "../includes/User.hpp"
#include "../includes/Channel.hpp"

User::User(Datas *datasPtr, int fd): _datasPtr(datasPtr), _fd(fd), _step(1), _op(0) {}

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

// INITIALIZER

const bool &User::getOp() const
{
	return _op;
}

// SETTERS

std::string	User::initUserName(string &userCmd)
{
	size_t	posSP;

	if (userCmd.find("USER ") != 0)
		throw std::invalid_argument("We are waiting for: USER <username>");
	posSP = userCmd.find_first_of(" ", 5);
	userCmd = userCmd.substr(5, posSP - 5);
	if (!userCmd.length())
		throw std::invalid_argument("No username found");
	if (userCmd.length() > 9)
		throw std::invalid_argument("The username passed is too long, please reduce to 9 caracteres");
	try {
		_datasPtr->getUser(userCmd);
		throw std::invalid_argument("The username passed is already assigned");
	} catch (datasException &e) {
		_userName = userCmd;
		sendMsgToClient(_fd, "Well " + _userName + ", now enter your nickname: ");
	}
	return ("Great ! You are now registered\nTo see all the availables commands, enter: /show");
}

std::string	User::initNickName(const usersDatas &users, string &nickCmd)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();
	size_t	posSP;

	if (nickCmd.find("NICK ") != 0)
		throw std::invalid_argument("We are waiting for: NICK <nickname>");
	posSP = nickCmd.find_first_of(" ", 5);
	nickCmd = nickCmd.substr(5, posSP - 5);
	if (!nickCmd.length())
		throw std::invalid_argument("No nickname found");
	if (nickCmd.length() > 9)
		throw std::invalid_argument("The nickname passed is too long, please reduce to 9 caracteres");
	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickCmd))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_nickName = nickCmd;
	return ("Well " + _nickName + ", now enter your username:");
}

// SETTERS

// UTILS

std::string	User::checkCAPLS(std::string &arg) {
	if (arg.compare(0, strlenP(arg), "CAP LS"))
		throw std::invalid_argument("You've to send us: CAP LS");
	return ("In order to use Ircserv, enter the commands in sequence\n1) PASS <password>\n2) NICK <nickname>\n3) USER <username>");
}

std::string	User::checkPwd(const std::string pwd, std::string &arg) {
	size_t	pos = arg.find("PASS ");

	if (pos != 0)
		throw std::invalid_argument("We are waiting for: PASS <password>");
	arg = arg.substr(5);
	if (!arg.length())
		throw std::invalid_argument("No password found");
	for (size_t i = 0; i < strlenP(arg) && i < pwd.length(); i++)
		std::cout << "i = " << i << " --> " << arg[i] - pwd[i] << std::endl;
	if (arg.compare(0, strlenP(arg), pwd))
		throw std::invalid_argument("The password passed isn't valid");
	return ("Great !! Now enter your nickname:");
}

void	User::addChannel(const string &chanName, bool role) {
	if (_channels.insert(make_pair(chanName, role)).second == false)
		throw datasException("User already in " + chanName , _userName);
}

// FUNCTIONS

const string	User::fillUser(string &arg) {
	string	msg;
	switch (_step) {
		case 1:
			msg = checkCAPLS(arg);
			break;
		case 2:
			msg = checkPwd(_datasPtr->getPwd(), arg);
			break;
		case 3:
			msg = initNickName(_datasPtr->getUsers(), arg);
			break;
		case 4:
			msg = initUserName(arg);
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
	return (msg);
}

void	User::execCmd(const string &cmd)
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

map<string, vector<string> > User::names(const vector<string> &channels)
{
	map<string, vector<string> > list;

	//LIST CHANNELS IN PARAMS
	if (!channels.empty())
	{
		for (vector<string>::const_iterator it = channels.begin(), ite = channels.end(); it != ite; it++)
		{
			vector<string> usersNames;
			map<string, bool> users;
			try
			{
				users = _datasPtr->getChannel(*it.base()).getUsers();
				for (map<string, bool>::const_iterator it = users.begin(), ite = users.end(); it != ite; it++)
				{
					if (it->second)
						usersNames.insert(usersNames.begin(), "@" + it->first);
					else
						usersNames.insert(usersNames.begin(), it->first);
				}
				list.insert(list.begin(), make_pair<string, vector<string> >(*it.base(), usersNames));
			}
			catch (datasException &e) {}
		}
	}
	else //LIST ALL CHANNELS 
	{
		for (channelsDatas::const_iterator it = _datasPtr->getChannels().begin(),
			ite = _datasPtr->getChannels().end(); it != ite; it++)
		{
			vector<string> usersNames;
			map<string, bool> users;
			try
			{
				users = it->second->getUsers();
				for (map<string, bool>::const_iterator it = users.begin(), ite = users.end(); it != ite; it++)
				{
					if (it->second)
						usersNames.insert(usersNames.begin(), "@" + it->first);
					else
						usersNames.insert(usersNames.begin(), it->first);
				}
				list.insert(make_pair<string, vector<string> >(it->first, usersNames));
			}
			catch (datasException &e) {}
		}
	}

	//ADD USER WITHOUT CHANNELS IN LIST
	vector<string> usersNames;
	for (usersDatas::const_iterator it = _datasPtr->getUsers().begin(),
		ite = _datasPtr->getUsers().end(); it != ite; it++)
	{
		if (it->second->getChannels().empty())
			usersNames.insert(usersNames.begin(), it->second->getUserName());
	}
	if (!usersNames.empty())
		list.insert(make_pair<string, vector<string> >("*", usersNames));

	//PRINT LIST
	for (map<string, vector<string> >::const_iterator it = list.begin(), ite = list.end(); it != ite; it++)
	{
		cout << it->first << endl;
		for (vector<string>::const_iterator vIt = it->second.begin(), vIte = it->second.end(); vIt != vIte; vIt++)
			cout << "\t" << *vIt.base() << endl;
	}
	return(list);
}

// CHAN OPERATOR FUNCTION

void	User::kick(const string &userName, const string &chanName)
{
	if (!_datasPtr->getChannel(chanName).userIsChanOp(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	_datasPtr->removeUserFromChannel(userName, chanName);
}

void	User::mode(const string &chanName, const int chanMode, const bool add) {
	Channel &chan = _datasPtr->getChannel(chanName);
	if (!chan.userIsChanOp(_userName))
		throw datasException("Not operator in " + chanName, _userName);
	chan.setMod(chanMode, add);
}

void	User::invite(const string &userName, const string &chanName) {
	Channel &chan = _datasPtr->getChannel(chanName);
	if (!chan.userIsChanOp(_userName))
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
