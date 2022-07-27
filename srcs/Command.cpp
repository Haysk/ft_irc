# include "../includes/Command.hpp"
# include "../includes/User.hpp"

Command::Command(void) : _cmd()
{
//	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["JOIN"] = &Command::join;
	_cmdMap["PART"] = &Command::part;
//	_cmdMap["PRIVMSG"] = &Command::privmsg;
	_cmdMap["PING"] = &Command::ping;
	_cmdMap["QUIT"] = &Command::quit;
	_cmdMap["KICK"] = &Command::kick;
	_cmdMap["MODE"] = &Command::mode;
	_cmdMap["INVITE"] = &Command::invite;
	_cmdMap["TOPIC"] = &Command::topic;
	_cmdMap["PASS"] = &Command::pass;
	_cmdMap["USER"] = &Command::user;
	_cmdMap["NICK"] = &Command::nick;
	
}

Command::~Command(void)
{
//	std::cout << "Command destructor called" << std::endl;
}

void	Command::checkCmd(User &user)
{
	void	(Command::*fct) (User&);
	std::string	str;

	str = _cmd.front();
	std::cout << "CMD: " << str << std::endl;
	for (mapper::iterator it = _cmdMap.begin();
		it != _cmdMap.end(); it++)
	{
		if (!(str.compare(it->first)))
		{
			fct = it->second;
			return ((this->*fct) (user));
		}
	}
	clearCmd();
	throw std::invalid_argument("You've entered a invalid command");
}

void	Command::buildCmd(size_t nOpt, std::string line)
{
	int	tmp = -1;
	size_t	pos;
	size_t	argLen;

	while (nOpt--)
	{
		pos = line.find_first_of(" ", tmp + 1);
		if (nOpt)
		{
			_cmd.push_back(line.substr(tmp + 1, pos - (tmp + 1)));
			tmp = pos;
		}
	}
	argLen = line.find_first_of(" ", tmp + 1);
	_cmd.push_back(line.substr(tmp + 1, argLen - (tmp + 1)));
}

void	Command::join(User &user)
{
	size_t	vecSize;

	if (_cmd.size() < 2)
		throw datasException("JOIN :Not enough parameters", 461);
	vector<string>	chans = explode(_cmd[1], ',');
	vecSize = chans.size();
	for (unsigned int i = 0; i < vecSize; i++)
		user.join(chans[i]);
}

void	Command::part(User &user)
{
	size_t	vecSize;

	if (_cmd.size() < 2)
		throw datasException("PART :Not enough parameters", 461);
	vector<string>	chans = explode(_cmd[1], ',');
	vecSize = chans.size();
	for (unsigned int i = 0; i < vecSize; i++)
		user.part(chans[i]);
}

void	Command::ping(User &user)
{
	if (_cmd.size() < 2)
		throw datasException(":No origin specified", 409);
	if (_cmd[1] != "MyIrc")
		throw datasException(_cmd[1] + " :No such server", 409);
	sendMsgToClient(user.getFd(), "MyIrc PONG MyIrc :MyIrc");
}

void	Command::kick(User &user)
{
	if (_cmd.size() < 3)
		throw datasException("KICK :Not enough parameters", 461);
	user.kick(_cmd[2], _cmd[1]);
}

void	Command::mode(User &user)
{
//	if (_cmd.size() == 2)
//		user.mode(_cmd[1], -1, 0);
	if (_cmd.size() < 3)
		throw datasException("MODE :Not enough parameters", 461);
	checkModeParam(_cmd[2]);
	user.mode(_cmd[1], convertModeParam(_cmd[2]), isAddMode(_cmd[2]));
}

void	Command::invite(User &user)
{
	if (_cmd.size() < 3)
		throw datasException("INVITE :Not enough parameters", 461);
	user.invite(_cmd[1], _cmd[2]);
}

void	Command::topic(User &user)
{
	if (_cmd.size() < 3)
		throw datasException("TOPIC :Not enough parameters", 461);
	user.topic(_cmd[1], _cmd[2]);
}

void	Command::quit(User &user)
{
	std::string	msg;
	int		i = 1;
	int		size = _cmd.size();

	if (size > 1)
	{
		while (i < size)
		{
			msg += _cmd[i];
			msg += " ";
			i++;
		}
		user.quit(msg);
	}
	else
		user.quit("");
}

void	Command::pass(User& user)
{
	(void)user;
	throw datasException(":Unauthorized command (already registered)", 462);
}

void	Command::user(User& user)
{
	(void)user;
	throw datasException(":Unauthorized command (already registered)", 462);
}

void	Command::nick(User& user)
{
	std::string	arg;
	size_t	i = 0;
	while (i < _cmd.size())
	{
		arg += _cmd[i];
		if (i + 1 != _cmd.size())
			arg += " ";
		i++;
	}
	user.nick(arg);
}

void	Command::displayCmd(void)
{
	unsigned int	i = 0;
	unsigned int	size = _cmd.size();

	for (i = 0; i < size; i++)
		std::cout << _cmd[i] << "; ";
	std::cout << std::endl;
}

void	Command::clearCmd(void)
{
	_cmd.clear();
}

void	checkModeParam(const std::string& param)
{
	if ((param[0] != '+' && param[0] != '-')
			|| (param.find_first_not_of("it", 1) != std::string::npos
			&& !checkDoublons(param)))
		throw std::invalid_argument("Error syntax\nHow to use: /topic <channel> <newName>");
}

int	convertModeParam(const std::string& param)
{
	int	ret = 0;

	if (param.find("i") != std::string::npos)
		ret = ret | MODE_I;
	if (param.find("t") != std::string::npos)
		ret = ret | MODE_T;
	return (ret);
}

bool	isAddMode(const std::string& param)
{
	if (param.find("+") != std::string::npos)
		return (true);
	return (false);
}
