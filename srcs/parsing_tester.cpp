# include "../includes/tester.hpp"

# define OPERATOR 1
# define BASIC 0

void	checkerCmd(Datas &servDatas, std::string cmd)
{
	Command	test(cmd);

	std::cout << "CMD: " << cmd << std::endl;
	try
	{
		// Parsing cmd : get User and channel and commands with options
		test.checkCmd(servDatas, servDatas.getUser("chikakah"));
		std::cout << "EXECUTION: " << cmd << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "***************\n" << std::endl;
}

int	checkerCmds(Datas &servDatas)
{
	servDatas.newUser("chikakah", "choko", "ipp", 100);
	std::cout << "\n\tPARSING TEST\n\n";
	/*------TEST WITH VALID OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH VALID OPERATOR CMDS------\n" << std::endl;
	checkerCmd(servDatas, "join channel");
	checkerCmd(servDatas, "part");
	checkerCmd(servDatas, "part channel");
	checkerCmd(servDatas, "part channel msg");
	checkerCmd(servDatas, "msg nickname msg");
	checkerCmd(servDatas, "query nickname");
	checkerCmd(servDatas, "query nickname msg");
	checkerCmd(servDatas, "quit");
	checkerCmd(servDatas, "quit msg");
	checkerCmd(servDatas, "kick nickname");
	checkerCmd(servDatas, "mode");
	checkerCmd(servDatas, "mode msg");
	checkerCmd(servDatas, "invite nickname");
	checkerCmd(servDatas, "topic");
	checkerCmd(servDatas, "topic msg");

	/*------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------\n" << std::endl;
	checkerCmd(servDatas, "kick");
	checkerCmd(servDatas, "mode");
	checkerCmd(servDatas, "invite");
	checkerCmd(servDatas, "topic");

	/*------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------*/
	std::cout << "\n------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------\n" << std::endl;
	checkerCmd(servDatas, "join");
	checkerCmd(servDatas, "join channel msg");
	checkerCmd(servDatas, "part channel msg nickname");
	checkerCmd(servDatas, "msg");
	checkerCmd(servDatas, "msg ncikname");
	checkerCmd(servDatas, "msg nickname msg channel");
	checkerCmd(servDatas, "query");
	checkerCmd(servDatas, "query nickname msg channel");
	checkerCmd(servDatas, "quit msg channel");
	checkerCmd(servDatas, "kick nickname msg");
	checkerCmd(servDatas, "kick");
	checkerCmd(servDatas, "mode msg channel");
	checkerCmd(servDatas, "invite nickname msg");
	checkerCmd(servDatas, "invite");
	checkerCmd(servDatas, "topic msg channel");
	return (0);
} 
