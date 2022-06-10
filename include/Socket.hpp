#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <functional>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>


class Socket {

    public:
        // Constructor / Destructor
        Socket(const char *ip, int port);
        Socket(const Socket &ref);
        ~Socket();

        // Operator
        Socket &operator=(const Socket &ref);

        // Attribut
        struct sockaddr_in _addr;
        const char *_ip;
        int _port;
        int _fd;
        int _max_fd;
        fd_set _readfs;
    
    public:
        // Method
        void CreateFd(int domain, int type, int protocol);
        void SetAddr(int domain);
        void Bind();
    
    //Exception
    class SocketFailed : public std::exception{
        public:
		const char* what() const throw();
    };

    class BindFailed : public std::exception{
        public:
    	const char* what() const throw();
    };
};