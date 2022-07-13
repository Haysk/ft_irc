# include "../includes/utils.hpp"

void	isAlpha(const std::string& str)
{
	int	i = 0;

	std::cout << "str : " << str << std::endl;
	while (str[i])
	{
		if (!((str[i] >= 65 && str[i] <= 90)
				|| (str[i] >= 97 && str[i] <= 122)
				|| (str[i] == 32)))
			throw std::invalid_argument("Not a alphabetic argument");
		i++;
	}
}

void	checkCmdName(const std::string cmdLine, const std::string expected)
{
	size_t	begin = cmdLine.find_first_not_of(" ");

	if (cmdLine.find(expected) != begin
			|| cmdLine.find_first_of(" ", begin) != begin + expected.length())
		throw std::invalid_argument("Invalid command");
}

void	checkRangeArg(const std::string cmdLine, size_t min, size_t max)
{
	size_t	nbrArg = countOccurrences(" ", cmdLine);

	if (nbrArg < min || nbrArg > max)
		throw std::invalid_argument("Number of arguments invalid");
}

void	checkNbrArg(const std::string cmdLine, size_t expected)
{
	if (countOccurrences(" ", cmdLine) != expected)
		throw std::invalid_argument("Number of arguments invalid");
}

void	checkLenArg(const std::string arg, size_t max)
{
	if (arg.length() > max)
		throw std::invalid_argument("Size of arg too long");
}

void	checkUserCmdNbrArg(const std::string& cmdLine,
		const std::string charset)
{
	size_t	count = 0;
	size_t	pos = 0;

	pos = cmdLine.find_first_not_of(charset);
	while (pos != std::string::npos && count < 4)
	{
		pos = getNextArgPos(cmdLine, pos, charset);
		count++;
	}
	if (count < 4 || pos == std::string::npos)
		throw std::invalid_argument("Argument.s missing");
	if (cmdLine[pos] != ':')
		throw std::invalid_argument("Missing ':' for realname");
	if (pos + 1 == cmdLine.length())
		throw std::invalid_argument("Argument.s missing");
}
