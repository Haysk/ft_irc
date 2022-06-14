#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "utils.hpp"

class Datas;
class User;

class	Command
{
	public:
		typedef	std::map<std::string, void (Command::*) (Datas&, User&)>	mapper;

	private:
		mapper	_cmdMap;
		std::deque<std::string>	_cmd;
		void	join(Datas&, User&);
		void	part(Datas&, User&);
		void	msg(Datas&, User&);
		void	query(Datas&, User&);
		void	quit(Datas&, User&);
		void	kick(Datas&, User&);
		void	mode(Datas&, User&);
		void	invite(Datas&, User&);
		void	topic(Datas&, User&);

	public:
		Command(std::string);
		~Command(void);
		void	buildCmd(size_t, std::string);
		void	checkCmd(Datas&, User&);
};

size_t	countOccurrences(std::string, std::string);
std::ostream& operator<<(std::ostream&, const Command&);
#endif
