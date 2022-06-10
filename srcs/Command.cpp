#include "../includes/Command.hpp"

Command::Command(std::string line)
{
	size_t	nOpt = countOccurrences(" ", line) + 1;

//	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["join"] = &Command::join;
	_cmdMap["part"] = &Command::part;
	_cmdMap["msg"] = &Command::msg;
	_cmdMap["query"] = &Command::query;
	_cmdMap["quit"] = &Command::quit;
	_cmdMap["kick"] = &Command::kick;
	_cmdMap["mode"] = &Command::mode;
	_cmdMap["invite"] = &Command::invite;
	_cmdMap["topic"] = &Command::topic;
	buildCmd(nOpt, line);
}

Command::~Command(void)
{
//	std::cout << "Command destructor called" << std::endl;
}

void	Command::checkCmd(Datas &servDatas, User &user)
{
	void	(Command::*fct) (Datas&, User&);
	std::string	str;

	str = _cmd.front();
	for (mapper::iterator it = _cmdMap.begin();
		it != _cmdMap.end(); it++)
	{
		if (!(str.compare(it->first)))
		{
			fct = it->second;
			return ((this->*fct) (servDatas, user));
		}
	}
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

void	Command::join(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /join <channel>");
	// user.join(channel);
}

void	Command::part(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
	if (_cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /part [channel] [msg]");
	// User.part(channel, msg)
}

void	Command::msg(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /msg <nickname> <msg>");
	// user.msg(nickname, msg))
}

void	Command::query(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
	if (_cmd.size() < 2 || _cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /query <nickname> [msg]");
	// user.query(nickname, msg)
}

void	Command::quit(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /quit [msg]");
	// user.quit(msg)
}

void	Command::kick(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
//	if (user.getRole(chanName))
//		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /kick <nickname>");
	// user.kick(nickname)
}

void	Command::mode(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
//	if (user.getRole(chanName))
//		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /mode [msg]");
	// user.mode(msg)
}

void	Command::invite(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
//	if (user.getrole(channame))
//		throw std::domain_error("you're not allowed to use this command");
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /invite <nickname>");
	// user.invite(nickname)
}

void	Command::topic(Datas &servDatas, User &user)
{
	(void)user;
	(void)servDatas;
//	if (user.getrole(channame))
//		throw std::domain_error("you're not allowed to use this command");
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /topic [msg]");
	// user.topic(msg)
}

size_t	countOccurrences(std::string charset, std::string str)
{
	size_t	count = 0;
	size_t	pos = 0;

	while ((pos = str.find_first_of(charset, pos + 1)) != std::string::npos)
		count++;
	return (count);
}
