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

const vector<string> explode(const string& s, const char& c)
{
	std::vector<std::string>	vec;
	std::string	sub;
	size_t		pos = s.find_first_of(c);
	size_t		start = 0;

	while (pos != std::string::npos)
	{
		vec.push_back(s.substr(start, pos - start));
		start = pos + 1;
		pos = s.find_first_of(c, start);
	}
	vec.push_back(s.substr(start));
	return (vec);
}

size_t	countOccurrences(std::string charset, const std::string str)
{
	size_t	count = 0;
	size_t	pos = 0;

	while ((pos = str.find_first_of(charset, pos + 1)) != std::string::npos)
		count++;
	return (count);
}
