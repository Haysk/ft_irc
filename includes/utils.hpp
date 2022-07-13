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
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <stdexcept>
#include <exception>
#include <stdint.h>
#include "Command.hpp"

#define IP "127.0.0.1"
#define PORT 8081
#define MODE_I 1
#define MODE_T 2
#define BITWISE_I 0
#define BITWISE_T 1

using namespace std;

void	sendMsgToClient(int fd, const std::string msg);

size_t	strlenP(std::string str);

const	vector<string> explode(const string& s, const char& c);

size_t	countOccurrences(std::string charset, const std::string str);

std::string	getArgAt(const std::string& str, size_t index,
			std::string charset);

std::string	getRealName(const std::string& str);

void	isAlpha(const std::string& str);


size_t	getNextArgPos(const std::string &str, size_t start,
			std::string charset);

	// REGISTRATION_CHECKER

void	checkCmdName(const std::string cmdLine, const std::string expected);

void	checkRangeArg(const std::string cmdLine, size_t min, size_t max);

void	checkNbrArg(const std::string cmdLine, size_t expected);

void	checkLenArg(const std::string arg, size_t max);

int	checkDoublons(const std::string str);

void	checkUserCmdNbrArg(const std::string& cmdLine, const std::string charset);

#endif //FT_IRC_UTILS_HPP
