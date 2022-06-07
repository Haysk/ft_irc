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

    private:
        // Attribut
        struct sockaddr_in _addr;
        const char *_ip;
        int _port;
        int _fd;
    
    public:
        // Method
        void CreateFd(int domain, int type, int protocol);
        void SetAddr(int domain);
        void Bind();

        int GetFd()const ;
        int GetPort()const;
        const char *GetIp();
        struct sockaddr_in *GetAddr();
};