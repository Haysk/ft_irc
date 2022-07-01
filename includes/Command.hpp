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
		void	show(User&);
		void	join(User&);
		void	part(User&);
		void	msg(User&);
		void	query(User&);
		void	quit(User&);
		void	kick(User&);
		void	mode(User&);
		void	invite(User&);
		void	topic(User&);
		/*
			// have to be build
			void	notice(Datas&, User&);
		*/

	public:
		Command(void);
		~Command(void);
		void	buildCmd(size_t, std::string);
		void	checkCmd(User&);
		void	displayCmd(void);
		void	clearCmd(void);
};

std::ostream& operator<<(std::ostream&, const Command&);
#endif
