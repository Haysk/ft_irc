# include "../includes/Command.hpp"

# define OPERATOR 1
# define BASIC 0

void	checker(bool type, std::string cmd)
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
	checker(OPERATOR, "join channel");
	checker(OPERATOR, "part");
	checker(OPERATOR, "part channel");
	checker(OPERATOR, "part channel msg");
	checker(OPERATOR, "msg nickname msg");
	checker(OPERATOR, "query nickname");
	checker(OPERATOR, "query nickname msg");
	checker(OPERATOR, "quit");
	checker(OPERATOR, "quit msg");
	checker(OPERATOR, "kick nickname");
	checker(OPERATOR, "mode");
	checker(OPERATOR, "mode msg");
	checker(OPERATOR, "invite nickname");
	checker(OPERATOR, "topic");
	checker(OPERATOR, "topic msg");

	/*------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------\n" << std::endl;
	checker(BASIC, "kick");
	checker(BASIC, "mode");
	checker(BASIC, "invite");
	checker(BASIC, "topic");

	/*------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------*/
	std::cout << "\n------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------\n" << std::endl;
	checker(OPERATOR, "join");
	checker(OPERATOR, "join channel msg");
	checker(OPERATOR, "part channel msg nickname");
	checker(OPERATOR, "msg");
	checker(OPERATOR, "msg ncikname");
	checker(OPERATOR, "msg nickname msg channel");
	checker(OPERATOR, "query");
	checker(OPERATOR, "query nickname msg channel");
	checker(OPERATOR, "quit msg channel");
	checker(OPERATOR, "kick nickname msg");
	checker(OPERATOR, "kick");
	checker(OPERATOR, "mode msg channel");
	checker(OPERATOR, "invite nickname msg");
	checker(OPERATOR, "invite");
	checker(OPERATOR, "topic msg channel");
	return (0);
}
