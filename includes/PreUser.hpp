#ifndef PREUSER_HPP
# define PREUSER_HPP

#include "Datas.hpp"
#include "utils.hpp"

class	PreUser
{
	private:
		int	_step;
		bool	_pwd;
		std::string	_username;
		std::string	_nickname;

	public:
		PreUser(void);

		//Need to be correclty define
		PreUser(int a){a = 42;};

		~PreUser(void);
		void	fillPreUser(Datas, std::string);
		void	checkPwd(std::string, std::string);
		void	setUsername(std::string);
		void	setNickname(std::string);
};
#endif
