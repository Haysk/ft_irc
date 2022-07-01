# include "../includes/Command.hpp"
# include "../includes/User.hpp"

Command::Command(void) : _cmd()
{
//	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["show"] = &Command::show;
	_cmdMap["join"] = &Command::join;
	_cmdMap["part"] = &Command::part;
	_cmdMap["msg"] = &Command::msg;
	_cmdMap["query"] = &Command::query;
	_cmdMap["quit"] = &Command::quit;
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

	while (nOpt--)
	{
		pos = line.find_first_of(" ", tmp + 1);
		if (nOpt)
		{
			_cmd.push_back(line.substr(tmp + 1, pos));
			tmp = pos;
		}
	}
	_cmd.push_back(line.substr(tmp + 1));
}

void	Command::show(User &user)
{
	sendMsgToClient(user.getFd(), "Command parts in <> are mandatory and in [] are optional\n/join <channel>\n/part [channel] [msg]\n/msg <nickname> <msg>\n/query <nickname> [msg]\n/quit [msg]\n/kick <nickname>\n/mode [msg]\n/invite <nickname>\n/topic [msg]");
}

void	Command::join(User &user)
{
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /join <canal>");
	user.joinChannel(_cmd[1]);
}

void	Command::part(User &user)
{
	(void)user;
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /part <canal>{,[canal]}");
	vector<string>	chans = explode(_cmd[1], ',');
	for (vector<string>::const_iterator it = chans.begin(), ite = chans.end();
			it != ite; it++)
	//	user.partChannel(it.base());
		std::cout << "USER not leaving: " << it.base() << std::endl;
}

void	Command::msg(User &user)
{
	(void)user;
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /msg <nickname> <msg>");
	// user.msg(nickname, msg))
}

void	Command::query(User &user)
{
	(void)user;
	if (_cmd.size() < 2 || _cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /query <nickname> [msg]");
	// user.query(nickname, msg)
}

void	Command::quit(User &user)
{
	(void)user;
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /quit [msg]");
	// user.quit(msg)
}

void	Command::kick(User &user)
{
	(void)user;
//	if (user.getRole(chanName))
//		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /kick <nickname>");
	// user.kick(nickname)
}

void	Command::mode(User &user)
{
	(void)user;
//	if (user.getRole(chanName))
//		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /mode [msg]");
	// user.mode(msg)
}

void	Command::invite(User &user)
{
	(void)user;
//	if (user.getrole(channame))
//		throw std::domain_error("you're not allowed to use this command");
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /invite <nickname>");
	// user.invite(nickname)
}

void	Command::topic(User &user)
{
	(void)user;
//	if (user.getrole(channame))
//		throw std::domain_error("you're not allowed to use this command");
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /topic [msg]");
	// user.topic(msg)
}

void	Command::displayCmd(void)
{
	unsigned int	i = 0;
	unsigned int	size = _cmd.size();

	for (i = 0; i < size; i++)
	{
		std::cout << _cmd[i] << "; ";
	}
	std::cout << std::endl;
}

void	Command::clearCmd(void)
{
	_cmd.clear();
}
