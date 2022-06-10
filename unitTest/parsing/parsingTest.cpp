# include "../../includes/Command.hpp"
# include "../../src/model/User.hpp"
# include "../../src/model/Channel.hpp"
# include "../../src/model/Datas.hpp"

# define OPERATOR 1
# define BASIC 0

void	checker(Datas &servDatas, std::string cmd)
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

int	parsingTest(Datas &servDatas)
{
	servDatas.newUser("chikakah", "choko", "ipp", 100);
	std::cout << "\tPARSING TEST\n\n";
	/*------TEST WITH VALID OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH VALID OPERATOR CMDS------\n" << std::endl;
	checker(servDatas, "join channel");
	checker(servDatas, "part");
	checker(servDatas, "part channel");
	checker(servDatas, "part channel msg");
	checker(servDatas, "msg nickname msg");
	checker(servDatas, "query nickname");
	checker(servDatas, "query nickname msg");
	checker(servDatas, "quit");
	checker(servDatas, "quit msg");
	checker(servDatas, "kick nickname");
	checker(servDatas, "mode");
	checker(servDatas, "mode msg");
	checker(servDatas, "invite nickname");
	checker(servDatas, "topic");
	checker(servDatas, "topic msg");

	/*------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------*/
	std::cout << "\n------TEST WITH BASIC TRYING TO EXEC OPERATOR CMDS------\n" << std::endl;
	checker(servDatas, "kick");
	checker(servDatas, "mode");
	checker(servDatas, "invite");
	checker(servDatas, "topic");

	/*------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------*/
	std::cout << "\n------TEST WITH OPERATOR TRYING TO EXEC INVALID CMDS------\n" << std::endl;
	checker(servDatas, "join");
	checker(servDatas, "join channel msg");
	checker(servDatas, "part channel msg nickname");
	checker(servDatas, "msg");
	checker(servDatas, "msg ncikname");
	checker(servDatas, "msg nickname msg channel");
	checker(servDatas, "query");
	checker(servDatas, "query nickname msg channel");
	checker(servDatas, "quit msg channel");
	checker(servDatas, "kick nickname msg");
	checker(servDatas, "kick");
	checker(servDatas, "mode msg channel");
	checker(servDatas, "invite nickname msg");
	checker(servDatas, "invite");
	checker(servDatas, "topic msg channel");
	return (0);
}
