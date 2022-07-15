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

void	sendMsgToClientInChan(const std::string sender, int fd, const std::string msg)
{
	int	lenS = sender.length();
	int	lenM = msg.length();
	int	i = 0;
	char	buf[lenS + lenM + 4];
 
	buf[i++] = '<';
	std::cout << "InChan2" << std::endl;
	while (i < lenS + 1)
	{
		buf[i] = sender[i - 1];
		i++;
	}
	buf[i++] = '>';
	buf[i++] = ' ';
	std::cout << "InChan2" << std::endl;
	while (i < lenS + lenM + 3)
	{
		buf[i] = msg[i - lenS - 3];
		i++;
	}
	buf[i] = '\n';
	std::cout << "InChan3" << std::endl;
	send(fd, buf, lenS + lenM + 4, 0);
	std::cout << "InChan4" << std::endl;
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

	pos = str.find_first_not_of(charset);
	while (pos != std::string::npos)
	{
		pos = getNextArgPos(str, pos, charset);
		count++;
	}
	return (count);
}

std::string	getArgAt(const std::string& str, size_t index,
			std::string charset)
{
	size_t	pos = str.find_first_not_of(charset);
	size_t	len;
	std::string	arg;

	while (index)
	{
		pos = str.find_first_of(charset, pos);
		pos = str.find_first_not_of(charset, pos);
		index--;
	}
	len = str.find_first_of(charset, pos);
	if (len != std::string::npos)
		arg = str.substr(pos, len - pos);
	else
		arg = str.substr(pos);
	isAlpha(arg);
	return (arg);
}

std::string	getArg(const std::string& str, size_t start,
			std::string charset)
{
	std::string	arg;
	size_t		pos = str.find_first_not_of(charset, start);
	size_t		len;

	if (pos == std::string::npos)
		throw std::invalid_argument("An argument is missing");
	len = str.find_first_of(charset, pos);
	if (len != std::string::npos)
		arg = str.substr(pos, len - pos);
	else
		arg = str.substr(pos);
	return (arg);
}

std::string	getRealName(const std::string& str)
{
	std::string	arg;
	size_t		pos = getNextArgPos(str, 0, " ");

	pos = getNextArgPos(str, pos, " ");
	pos = getNextArgPos(str, pos, " ");
	pos = getNextArgPos(str, pos, " ");
	if (pos == std::string::npos)
		throw std::invalid_argument("RealName is missing");
	if (pos != str.find_first_of(":"))
		throw std::invalid_argument("Missing ':' for realname");
	arg = str.substr(pos + 1);
	isAlpha(arg);
	return (arg);
}

int	checkDoublons(const std::string str)
{
	int	strLen = str.length();

	for (int i = 0; i < strLen - 1; i++)
	{
		for (int j = i + 1; j < strLen; j++)
		{
			if (str[i] == str[j])
				return (0);
		}
	}
	return (1);
}

size_t	getNextArgPos(const std::string &str, size_t start, std::string charset)
{
	size_t	pos;

	pos = str.find_first_of(charset, start);
	pos = str.find_first_not_of(charset, pos);
	return (pos);
}
