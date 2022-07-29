# include "../includes/Command.hpp"
# include "../includes/User.hpp"
# include "../includes/Channel.hpp"

Command::Command(void) : _cmd()
{
	_cmdMap["JOIN"] = &Command::join;
	_cmdMap["PART"] = &Command::part;
	_cmdMap["PRIVMSG"] = &Command::privmsg;
	_cmdMap["NOTICE"] = &Command::notice;
	_cmdMap["PING"] = &Command::ping;
	_cmdMap["QUIT"] = &Command::quit;
	_cmdMap["KICK"] = &Command::kick;
	_cmdMap["MODE"] = &Command::mode;
	_cmdMap["INVITE"] = &Command::invite;
	_cmdMap["TOPIC"] = &Command::topic;
	_cmdMap["PASS"] = &Command::pass;
	_cmdMap["USER"] = &Command::user;
	_cmdMap["NICK"] = &Command::nick;
	_cmdMap["WHO"] = &Command::who;
}

Command::~Command(void)
{
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
	string	arg;

	pos = line.find_first_of(" ", tmp + 1);
	arg = line.substr(tmp + 1, pos - (tmp + 1));
	_cmd.push_back(arg);
	tmp = pos;
	if (!arg.compare("PRIVMSG") || !arg.compare("PART")
		|| !arg.compare("KICK") || !arg.compare("QUIT")
		|| !arg.compare("TOPIC") || !arg.compare("NOTICE"))
	{
		buildCmdWithMsg(getNArgsCmdMsg(arg), line);
		return ;
	}
	while (nOpt--)
	{
		pos = line.find_first_of(" ", tmp + 1);
		if (nOpt)
		{
			arg = line.substr(tmp + 1, pos - (tmp + 1));
			_cmd.push_back(arg);
			tmp = pos;
		}
	}
	argLen = line.find_first_of(" ", tmp + 1);
	_cmd.push_back(line.substr(tmp + 1, argLen - (tmp + 1)));
}

void	Command::buildCmdWithMsg(int nArgs, const string& line)
{
	size_t	end;
	size_t	begin;

	end = _cmd[0].length();
	while (nArgs-- > 0)
	{
		begin = line.find_first_not_of(" ", end);
		end = line.find_first_of(" ", begin);
		_cmd.push_back(line.substr(begin, end - begin));
	}
	begin = line.find_first_of(":", end);
	if (begin != std::string::npos)
		_cmd.push_back(line.substr(begin + 1));
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
	string	msg = "";

	if (_cmd.size() < 2)
		throw datasException("PART :Not enough parameters", 461);
	vector<string>	chans = explode(_cmd[1], ',');
	vecSize = chans.size();
	if (_cmd.size() == 3)
		msg = _cmd[2];
	for (unsigned int i = 0; i < vecSize; i++)
		user.part(chans[i], msg);
}

void	Command::privmsg(User &user) 
{
	if (_cmd.size() < 2)
		throw datasException(":No recipient given (PRIVMSG)", 411); // ERR_NORECIPIENT
	if (_cmd.size() < 3)
		throw datasException(_cmd[1] + " :No text to send", 412);
	user.privMsg(_cmd[1], _cmd[2]);
}

void	Command::notice(User &user)
{
	if (_cmd.size() > 2)
		user.notice(_cmd[1], _cmd[2]);
}

void	Command::ping(User &user)
{
	if (_cmd.size() < 2)
		throw datasException(":No origin specified", 409);
	if (_cmd[1] != "ircserv")
		throw datasException(_cmd[1] + " :No such server", 409);
	sendMsgToClient(user.getFd(), ":ircserv PONG ircserv :ircserv");
}

void	Command::kick(User &user)
{
	string	msg = "";
	if (_cmd.size() < 3)
		throw datasException("KICK :Not enough parameters", 461);
	if (_cmd.size() == 4)
		msg = _cmd[3];
	user.kick(_cmd[2], _cmd[1], msg);
}

void	Command::mode(User &user)
{
	if (_cmd.size() == 2)
	{
		user.mode(_cmd[1], -1, 0);
		return ;
	}
	checkModeParam(user.getDatasPtr(), _cmd[2], _cmd[1], user.getUserName());
	user.mode(_cmd[1], convertModeParam(_cmd[2]), isAddMode(_cmd[2]), _cmd[2]);
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
		user.topic(_cmd[1]);
	else
		user.topic(_cmd[1], _cmd[2]);
}

void	Command::quit(User &user)
{
	if (_cmd.size() > 1)
		user.quit(_cmd[1]);
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

void	Command::who(User& user)
{
	(void)user;
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

void	checkModeParam(Datas* datas, const std::string& param,
		const std::string& chanName, const std::string& userName)
{
	try {
		datas->getUser(chanName, NICKNAME);
	}
	catch (datasException& e) {
		if (!datas->getChannel(chanName).userIsChanOp(userName))
			throw datasException(chanName + " You're not channel operator", 482);
		if ((param[0] != '+' && param[0] != '-')
				|| param.find_first_not_of("it", 1) != std::string::npos
				|| !checkDoublons(param))
			throw datasException(param + " :is unknown mode char to me for " + chanName, 472);
		return ;
	}
	throw datasException(":Unknown MODE flag", 501);
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

int	getNArgsCmdMsg(const string& cmd)
{
	if (!cmd.compare("KICK"))
		return (2);
	else if (!cmd.compare("QUIT"))
		return (0);
	else if (!cmd.compare("PRIVMSG") || !cmd.compare("PART") || !cmd.compare("TOPIC") || !cmd.compare("NOTICE"))
		return (1);
	return (0);
}
