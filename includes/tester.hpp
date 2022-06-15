# include "../includes/Command.hpp"
# include "../includes/User.hpp"
# include "../includes/Channel.hpp"
# include "../includes/Datas.hpp"

# define OPERATOR 1
# define BASIC 0

typedef struct	s_recv
{
	int		fd;
	std::string	cmd;
}		t_recv;

void	checkerCmd(Datas &servDatas, std::string cmd);

int	checkerCmds(Datas &servDatas);

t_recv	getRecv(void);

void	treatCmd(Datas &servDatas, t_recv rec);

void	checkerPreUsers(Datas &servDatas);
