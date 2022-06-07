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

class Socket;

class Server {
    public:
        // Constructor / Destructor
        Server();
        Server(const Server &ref);
        ~Server();

        // Operator
        Server &operator=(const Server &ref);

    private:
        //Attribut
        int _id;
        char *_buff;
        int _csock; //client socket
        fd_set _readfs;

    public:
    void    Listen(Socket sk, int backlog);
    void    Select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);
    void    Accept(int sockfd, struct sockaddr *addr, socklen_t *len);


        
};