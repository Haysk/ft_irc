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
#include <sys/socket.h>

class Socket;

class Server {
    public:
        // Constructor / Destructor
        Server();
        Server(const Server &ref);
        ~Server();

        // Operator
        Server &operator=(const Server &ref);

        //Attribut
        int _id;
        char *_buff;


    public:
    void    Listen(Socket *sk, int backlog);
    void    Select(Socket *sk, struct timeval *timeout);
    void    Accept(Socket *sk);
    void    Recv(Socket *sk, int idx_client, int flag);

    //Exception
    class ListenFailed : public std::exception{
        public:
    	const char* what() const throw();
    };

    class SelectFailed : public std::exception{
        public:
    	const char* what() const throw();
    };     

};