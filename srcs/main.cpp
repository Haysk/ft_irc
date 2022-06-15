# include "../includes/Command.hpp"
# include "../includes/User.hpp"
# include "../includes/Channel.hpp"
# include "../includes/Datas.hpp"
# include "../includes/tester.hpp"

int	main(void)
{
	std::string	pwd = "hello";
	Datas		*servDatas = new Datas(pwd);
	int		test;

	std::cout << "To test the parsing, press 1\nTo test the registration process, press 2\n>> ";
	std::cin >> test;
	if (test == 1)
		checkerCmds(*servDatas);
	else if (test == 2)
		checkerPreUsers(*servDatas);
	delete servDatas;
	return (0);
}
