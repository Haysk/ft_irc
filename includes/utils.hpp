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

size_t	getNextArgPos(const std::string &str, size_t start, std::string charset);

std::string	getNextArg(const std::string& str, size_t start,
			std::string charset);

std::string	getArg(const std::string& str, size_t start,
			std::string charset);

std::string	getRealName(const std::string& str, size_t start);

void	isAlpha(const std::string& str);

#endif //FT_IRC_UTILS_HPP
