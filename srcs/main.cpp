# include "../includes/Command.hpp"
# include "../includes/User.hpp"
# include "../includes/Channel.hpp"
# include "../includes/Datas.hpp"

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

typedef struct	s_recv
{
	int		fd;
	std::string	cmd;
}		t_recv;

t_recv	getRecv(void)
{
	t_recv	rec;

	std::cout << "Entrez votre FD: "; 
	std::cin >> rec.fd;
	std::cout << "Entrez votre commande: ";
	std::cin >> rec.cmd;
	return (rec);
}

void	treatCmd(Datas &servDatas, t_recv rec)
{
	usersDatas2		usersData = servDatas.getUsers2();
	usersDatas_const_it2	it = usersData.find(rec.fd);

	if (it == usersData.end())
	{
		std::cout << "Welcome to my server, please enter the password"
			<< std::endl;
		servDatas.newUser2(rec.fd);
	}
	else
	{
		it->second->fillUser(servDatas, rec.cmd);
	}
}

void	checkerPreUsers(Datas &servDatas)
{
	t_recv	rec;

	rec = getRecv();
	while (1)
	{
		try
		{
			treatCmd(servDatas, rec);
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR: " << e.what() << std::endl;
		}
		rec = getRecv();
	}
}

int	main(void)
{
	std::string	pwd = "hello";
	Datas		*servDatas = new Datas(pwd);

//	checkerCmds(*servDatas);
	checkerPreUsers(*servDatas);
	delete servDatas;
	return (0);
}
