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

	while (pos != std::string::npos)
	{
		pos = getNextArgPos(str, pos, charset);
		count++;
	}
	return (count);
}

size_t	getNextArgPos(const std::string &str, size_t start, std::string charset)
{
	size_t	pos;

	pos = str.find_first_of(charset, start);
	pos = str.find_first_not_of(charset, pos);
	return (pos);
}

std::string	getNextArg(const std::string& str, size_t start,
			std::string charset)
{
	std::string	next;
	size_t		pos;
	size_t		len;

	pos = getNextArgPos(str, start, charset);
	if (pos == std::string::npos)
		throw std::invalid_argument("An argument is missing");
	len = str.find_first_of(charset, pos);
	if (len != std::string::npos)
		next = str.substr(pos, len - pos);
	else
		next = str.substr(pos);
	isAlpha(next);
	return (next);
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

std::string	getRealName(const std::string& str, size_t start)
{
	std::string	arg;
	size_t		pos = getNextArgPos(str, start, " ");

	if (pos == std::string::npos)
		throw std::invalid_argument("An argument is missing");
	if (pos != str.find_first_of(":"))
		throw std::invalid_argument("Missing ':' for realname");
	arg = str.substr(pos + 1);
	isAlpha(arg);
	return (arg);
}

void	isAlpha(const std::string& str)
{
	int	i = 0;

	while (str[i])
	{
		if (!((str[i] >= 65 && str[i] <= 90)
				|| (str[i] >= 97 && str[i] <= 122)
				|| (str[i] == 32)))
			throw std::invalid_argument("Not a alphabetic argument");
		i++;
	}
}
