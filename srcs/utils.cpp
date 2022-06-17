# include "../includes/utils.hpp"

void	sendMsgToClient(int fd, const std::string msg)
{
	int	len = msg.length() + 1;
	int	i;
	char	buf[len];
 
	for (i = 0; i < len - 1; i++)
		buf[i] = msg[i];
	buf[i] = '\n';
	send(fd, buf, len, 0);
}
