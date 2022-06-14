#include "../includes/PreUser.hpp"

PreUser::PreUser(): _step(1), _pwd(false), _username(""), _nickname("")
{
	std::cout << "PreUser default constructor called" << std::endl;
}

PreUser::~PreUser(void)
{
	std::cout << "PreUser destructor called" << std::endl;
}

void	PreUser::fillPreUser(Datas servDatas, std::string arg)
{
	switch (_step)
	{
		case 1:
			checkPwd(servDatas.getPwd(), arg);
			break;
		case 2:
			setUsername(arg);
			break;
		case 3:
			setNickname(arg);
			break;
		default:
			throw std::out_of_range("The preUser is already complete");
	}
	_step++;
}

void	PreUser::checkPwd(const std::string pwd, std::string arg)
{
	if (!_pwd)
	{
		if (pwd.compare(arg))
		{
			throw std::invalid_argument("The password passed isn't valid");
		}
	}
	_pwd = true;
}

void	PreUser::setUsername(std::string arg)
{
	_username = arg;
}

void	PreUser::setNickname(std::string arg)
{
	_nickname = arg;
}
