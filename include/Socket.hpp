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
#define IP "127.0.0.1"
#define LIMIT_MSG 512

class Socket {

    public:
        // Constructor / Destructor
        Socket();
        Socket(const Socket &ref);
        ~Socket();

        // Operator
            Socket &operator=(const Socket &ref);

    private:
        // Attribut
        struct sockaddr_in _addr;
        socklen_t _len;
    
    public:
        // Method
        int CreateFd();
        int SetAddr();
        int Bind();
};