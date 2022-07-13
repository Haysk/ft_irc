# include "../includes/Command.hpp"
# include "../includes/User.hpp"

Command::Command(void) : _cmd()
{
//	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["show"] = &Command::show;
	_cmdMap["join"] = &Command::join;
	_cmdMap["part"] = &Command::part;
	_cmdMap["kick"] = &Command::kick;
	_cmdMap["mode"] = &Command::mode;
	_cmdMap["invite"] = &Command::invite;
	_cmdMap["topic"] = &Command::topic;
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

void	Command::show(User &user)
{
	sendMsgToClient(user.getFd(), "Command parts in <> are mandatory and in [] are optional\n/join <channel>\n/part [channel] [msg]\n/msg <nickname> <msg>\n/query <nickname> [msg]\n/quit [msg]\n/kick <nickname>\n/mode [msg]\n/invite <nickname>\n/topic [msg]");
}

void	Command::join(User &user)
{
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /join <channel>");
	user.join(_cmd[1]);
}

void	Command::part(User &user)
{
	size_t	vecSize;

	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /part <channel>{,[channel]}");
	vector<string>	chans = explode(_cmd[1], ',');
	vecSize = chans.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		user.part(chans[i]);
		std::cout << "USER leaving: " << chans[i] << std::endl;
	}
}

void	Command::kick(User &user)
{
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /kick <channel> <nickname>");
	if (!user.getOp(_cmd[1]))
		throw std::domain_error("You're not allowed to use this command");
	std::cout << "KICK" << std::endl;
	user.kick(_cmd[2], _cmd[1]);
}

void	Command::mode(User &user)
{
	if (_cmd.size() != 3)
		throw std::invalid_argument("Invalid number of argument.s");
	if (!user.getOp(_cmd[1]))
		throw std::domain_error("You're not allowed to use this command");
	//throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /mode <channel> <{+|-}{i|t}>");
	checkModeParam(_cmd[2]);
	user.mode(_cmd[1], convertModeParam(_cmd[2]), isAddMode(_cmd[2]));
}

void	Command::invite(User &user)
{
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /invite <nickname> <channel>");
	if (!user.getOp(_cmd[2]))
		throw std::domain_error("You're not allowed to use this command");
	user.invite(_cmd[1], _cmd[2]);
}

void	Command::topic(User &user)
{
	if (_cmd.size() > 3 || _cmd.size() < 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /topic <channel> [name]");
	if (!user.getOp(_cmd[1]))
		throw std::domain_error("You're not allowed to use this command");
	user.topic(_cmd[1], _cmd[2]);
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
	if (param[0] != '+' && param[0] != '-')
		throw std::invalid_argument("Missing + or - in front of mode parameter");
	if (param.find_first_not_of("it", 1) != std::string::npos && !checkDoublons(param))
		throw std::invalid_argument("Invalid mode parameter");
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
