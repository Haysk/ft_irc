#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
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
#include <vector>

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
        std::vector<int> _csock; // client socket
        //Attribut
        // int _csock;
        int _id;
        char *_buff;
        fd_set _readfs;

    public:
    void    Listen(Socket sk, int backlog);
    void    Select(int fd, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);
    void    Accept(Socket sk);
    void    Recv(int fd,int flag);

    fd_set        *GetReadFs();
    int           GetFdMax();
    int           GetId();
    char          *GetBuff();

    //Exception
    class ListenFailed : public std::exception{
        public:
    	const char* what() const throw();
    };

    class SelectFailed : public std::exception{
        public:
    	const char* what() const throw();
    };     

    // class AcceptFailed : public std::exception{
    //     public:
    // 	const char* what() const throw();
    // };

    // class RecvFailed : public std::exception{
    //     public:
    // 	const char* what() const throw();
    // };
};