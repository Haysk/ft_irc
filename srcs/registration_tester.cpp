# include "../includes/tester.hpp"

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
	usersDatas		usersData = servDatas.getUsers();
	usersDatas_const_it	it = usersData.find(rec.fd);

	if (it == usersData.end())
	{
		std::cout << "Welcome to my server, please enter the password"
			<< std::endl;
		servDatas.newUser(rec.fd);
	}
	else
	{
		it->second->fillUser(rec.cmd);
	}
}

void	checkerPreUsers(Datas &servDatas)
{
	t_recv	rec;

	std::cout << "\n\tREGISTRATION TESTER\n" << std::endl;
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
