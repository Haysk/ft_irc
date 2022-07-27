# include "../includes/utils.hpp"
# include <ctime>
#include <fstream>

void	sendMsgToClient(int fd, const std::string &msg)
{
	int	len = msg.length() + 2;
	int	i;
	char	buf[len];

	for (i = 0; i < len - 1; i++)
		buf[i] = msg[i];
	buf[i++] = '\n';
	buf[i] = '\0';
	std::cout << "MSG SEND TO " << fd << " : " << buf << std::endl;
	send(fd, buf, i, 0);
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
			std::string charset, int config)
{
	size_t	pos = str.find_first_not_of(charset);
	size_t	len;
	std::string	arg;

	while (pos != std::string::npos && index)
	{
		pos = str.find_first_of(charset, pos);
		pos = str.find_first_not_of(charset, pos);
		index--;
	}
	if (pos == std::string::npos)
		return ("");
	if (!config)
	{
		len = str.find_first_of(charset, pos);
		if (len != std::string::npos)
			arg = str.substr(pos, len - pos);
		else
			arg = str.substr(pos);
	}
	else
	{
		if (pos == std::string::npos)
			throw std::invalid_argument("Argument.s missing");
		if (pos != str.find_first_of(":"))
			throw std::invalid_argument("Missing ':' for the last argument");
		pos = str.find_first_not_of(" ", pos + 1);
		arg = str.substr(pos);
	}
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

std::string	getMsgMode(const int chanMode, const bool add)
{
	std::string	msg;

	if (add)
		msg = "ADD THE MODE ";
	else
		msg = "REMOVE THE MODE ";
	switch (chanMode)
	{
		case 1:
			msg += "<<INVITATION ONLY>>";
			break;
		case 2:
			msg += "<<TOPIC EDITABLE BY OPERATORS>>";
			break;
		case 3:
			msg += "<<INVITATION ONLY>> and <<TOPIC EDITABLE BY OPERATORS>>";
	}
	return (msg);
}

map<string, string> getOperatorsConf()
{
	map<string, string> list;
	ifstream conf ("irc.conf");

	if (!conf.is_open())
		throw std::invalid_argument("irc.conf is missing");
	string line;
	while(getline(conf, line)) {
		for(string::iterator it = line.begin(), ite = line.end(); it != ite; it++)
			if (isspace(*it.base()))
				line.erase(it);
		size_t delimiter = line.find('=');
		if (delimiter == line.npos)
			throw std::invalid_argument("irc.conf is bad");
		string name = line.substr(0, delimiter);
		string pass = line.substr(delimiter + 1);
		list.insert(make_pair(name, pass));
	}
	return list;
}
