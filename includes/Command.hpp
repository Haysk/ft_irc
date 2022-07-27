#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "utils.hpp"

class User;

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
		void	quit(User&);
		void	ping(User&);
		void	kick(User&);
		void	mode(User&);
		void	invite(User&);
		void	topic(User&);
		void	pass(User&);
		void	user(User&);
		void	nick(User&);

	public:
		Command(void);
		~Command(void);
		void	buildCmd(size_t, std::string);
		void	buildCmdPrivmsg(std::string);
		void	checkCmd(User&);
		void	displayCmd(void);
		void	clearCmd(void);
};

void	checkModeParam(const std::string& param);

int	convertModeParam(const std::string& param);

bool	isAddMode(const std::string& param);
#endif
