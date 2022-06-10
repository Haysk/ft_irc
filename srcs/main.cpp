# include "../includes/Command.hpp"

void	checker(std::string type, std::string cmd)
{
	Command	test(type, cmd);

	std::cout << "CMD: " << cmd << std::endl;
	try
	{
		test.CheckCmd();
		std::cout << "EXECUTION: " << cmd << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "***************\n" << std::endl;
}

int	main(void)
{
	/*------TEST WITH VALID OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH VALID OPERATOR CMDS------\n" << std::endl;
	checker("operator", "join channel");
	checker("operator", "part");
	checker("operator", "part channel");
	checker("operator", "part channel msg");
	checker("operator", "msg nickname msg");
	checker("operator", "query nickname");
	checker("operator", "query nickname msg");
	checker("operator", "quit");
	checker("operator", "quit msg");
	checker("operator", "kick nickname");
	checker("operator", "mode");
	checker("operator", "mode msg");
	checker("operator", "invite nickname");
	checker("operator", "topic");
	checker("operator", "topic msg");

	/*------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------\n" << std::endl;
	checker("basic", "kick");
	checker("basic", "mode");
	checker("basic", "invite");
	checker("basic", "topic");

	/*------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------*/
	std::cout << "\n------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------\n" << std::endl;
	checker("operator", "join");
	checker("operator", "join channel msg");
	checker("operator", "part channel msg nickname");
	checker("operator", "msg");
	checker("operator", "msg ncikname");
	checker("operator", "msg nickname msg channel");
	checker("operator", "query");
	checker("operator", "query nickname msg channel");
	checker("operator", "quit msg channel");
	checker("operator", "kick nickname msg");
	checker("operator", "kick");
	checker("operator", "mode msg channel");
	checker("operator", "invite nickname msg");
	checker("operator", "invite");
	checker("operator", "topic msg channel");
	return (0);
}
