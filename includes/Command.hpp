#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "utils.hpp"

class User;
class Datas;

class	Command
{
	public:
		typedef	std::map<std::string, void (Command::*) (User&)>	mapper;

	private:
		mapper	_cmdMap;
		std::deque<std::string>	_cmd;
		void	join(User&);
		void	part(User&);
		void	privmsg(User&);
		void	notice(User&);
		void	quit(User&);
		void	ping(User&);
		void	kick(User&);
		void	mode(User&);
		void	invite(User&);
		void	topic(User&);
		void	pass(User&);
		void	user(User&);
		void	nick(User&);
		void	who(User&);

	public:
		Command(void);
		~Command(void);
		void	buildCmd(size_t, std::string);
		void	buildCmdWithMsg(int NArgs, const std::string&);
		void	checkCmd(User&);
		void	displayCmd(void);
		void	clearCmd(void);
};

void	checkModeParam(Datas* datas, const std::string& param, const std::string& chanName);

int	convertModeParam(const std::string& param);

bool	isAddMode(const std::string& param);

int	getNArgsCmdMsg(const std::string& cmd);
#endif
