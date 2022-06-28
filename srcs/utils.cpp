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

size_t	strlenP(std::string str)
{
	size_t	l = 0;

	while (str[l] && str[l] >= 32 && str[l] <= 126)
		l++;
	return (l);
}
