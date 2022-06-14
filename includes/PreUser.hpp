#ifndef PREUSER_HPP
# define PREUSER_HPP
# include <string>
# include <iostream>
# include <string>
# include <map>
# include <deque>
# include <cstdio>
# include "../includes/Channel.hpp"
# include "../includes/User.hpp"
# include "../includes/Datas.hpp"

class	Datas;

class	PreUser
{
	private:
		int	_step;
		bool	_pwd;
		std::string	_username;
		std::string	_nickname;

	public:
		PreUser(void);
		~PreUser(void);
		void	fillPreUser(Datas, std::string);
		void	checkPwd(std::string, std::string);
		void	setUsername(std::string);
		void	setNickname(std::string);
};
#endif
