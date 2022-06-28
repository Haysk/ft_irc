#include "../includes/User.hpp"

User::User(int fd): _fd(fd), _step(1) {}

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

std::string	User::initUserName(const usersDatas &users, string &userName)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();
	size_t	posSP;

	if (userName.find("USER ") != 0)
		throw std::invalid_argument("We are waiting for: USER <username>");
	posSP = userName.find_first_of(" ", 5);
	userName = userName.substr(5, posSP - 5);
	if (!userName.length())
		throw std::invalid_argument("No username found");
	if (userName.length() > 9)
		throw std::invalid_argument("The username passed is too long, please reduce to 9 caracteres");
	while (it != ite)
	{
		if (!it->second->getUserName().compare(userName))
			throw std::invalid_argument("The username passed is already assigned");
		it++;
	}
	_userName = userName;
	return ("Great ! You are now registered\nTo see all the availables commands, enter: /show");
}

std::string	User::initNickName(const usersDatas &users, string &nickName)
{
	usersDatas_const_it	it = users.begin();
	usersDatas_const_it	ite = users.end();
	size_t	posSP;

	if (nickName.find("NICK ") != 0)
		throw std::invalid_argument("We are waiting for: NICK <nickname>");
	posSP = nickName.find_first_of(" ", 5);
	nickName = nickName.substr(5, posSP - 5);
	if (!nickName.length())
		throw std::invalid_argument("No nickname found");
	if (nickName.length() > 9)
		throw std::invalid_argument("The nickname passed is too long, please reduce to 9 caracteres");
	while (it != ite)
	{
		if (!it->second->getNickName().compare(nickName))
			throw std::invalid_argument("The nickname passed is already assigned");
		it++;
	}
	_nickName = nickName;
	return ("Well " + _nickName + ", now enter your username:");
}

// SETTERS

// UTILS

std::string	User::checkCAPLS(std::string arg) {
	std::cout << "arg: " << arg << "|" << std::endl;
	if (arg.compare(0, strlenP(arg), "CAP LS"))
		throw std::invalid_argument("You've to send us: CAP LS");
	return ("In order to use Ircserv, enter the commands in sequence\n1) PASS <password>\n2) NICK <nickname>\n3) USER <username>");
}

std::string	User::checkPwd(const std::string pwd, std::string arg) {
	size_t	pos = arg.find("PASS ");

	if (pos != 0)
		throw std::invalid_argument("We are waiting for: PASS <password>");
	arg = arg.substr(5);
	if (!arg.length())
		throw std::invalid_argument("No password found");
	if (pwd.compare(0, strlenP(arg), arg))
		throw std::invalid_argument("The password passed isn't valid");
	return ("Great !! Now enter your nickname:");
}

void	User::addChannel(const string &chanName, bool role) {
	if (_channels.insert(make_pair(chanName, role)).second == false)
		throw datasException("User aleady in " + chanName , _userName);
}

// FUNCTIONS

std::string	User::fillUser(Datas &servDatas, std::string arg) {
	std::string	msg;
	switch (_step) {
		case 1:
			msg = checkCAPLS(arg);
			break;
		case 2:
			msg = checkPwd(servDatas.getPwd(), arg);
			break;
		case 3:
			msg = initNickName(servDatas.getUsers(), arg);
			break;
		case 4:
			msg = initUserName(servDatas.getUsers(), arg);
			break;
		default:
			throw std::out_of_range("This user is already complete");
	}
	_step++;
	return (msg);
}

void	User::execCmd(Datas &servDatas, std::string cmd)
{
	Command	command(cmd);

	command.checkCmd(servDatas, *this);
	std::cout << "EXECUTION: " + cmd + " by " + _userName;
	sendMsgToClient(_fd, "EXECUTION: " + cmd + " by " + _userName);
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
