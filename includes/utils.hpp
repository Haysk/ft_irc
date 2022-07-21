//
// Created by adylewsk on 5/31/22.
//

#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cerrno>
#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <stdexcept>
#include <exception>
#include <stdint.h>
#include <ctime>
#include <fstream>
#include "Command.hpp"

#define IP "127.0.0.1"
#define PORT 8081
#define MODE_I 1
#define MODE_T 2
#define BITWISE_I 0
#define BITWISE_T 1
#define USERNAME 0
#define NICKNAME 1

#define SERVLOGO "(  \x5c/  )( \x5c/ )___(_  _)(  _ \x5c / __)\n )    (  \x5c  /(___)_)(_  )   /( (__\n(_/\x5c/\x5c_) (__)    (____)(_)\x5c_) \x5c___)\n"


using namespace std;

void	signal_handler(int n);

bool	check_input(int ac, char **av);

void	sendMsgToClient(int fd, const std::string msg);

void	sendMsgToClientInChan(const std::string sender, int fd, const std::string msg);

void	cleanScreen(int fd);

size_t	strlenP(std::string str);

const	vector<string> explode(const string& s, const char& c);

size_t	countOccurrences(std::string charset, const std::string str);

std::string	getArgAt(const std::string& str, size_t index,
			std::string charset);

std::string	getRealName(const std::string& str);


size_t	getNextArgPos(const std::string &str, size_t start,
			std::string charset);

	// REGISTRATION_CHECKER

void	isAlphaNum(const std::string& str);

void	isAlpha(const std::string& str);

void	checkCmdName(const std::string cmdLine, const std::string expected);

void	checkRangeArg(const std::string cmdLine, size_t min, size_t max);

void	checkNbrArg(const std::string cmdLine, size_t expected);

void	checkLenArg(const std::string arg, size_t max);

int		checkDoublons(const std::string str);

void	checkUserCmdNbrArg(const std::string& cmdLine, const std::string charset);

map<string, string>	getOperatorsConf();

string	getMsgMode(const int chanMode, const bool add);

#endif //FT_IRC_UTILS_HPP
