#include "Server.hpp"
#include "Socket.hpp"
#define LIMIT_MSG 512


Server::Server():1
_csock(-1),
_id(0){
    this->_buff = new char[LIMIT_MSG];
    memset(buff, 0, LIMIT_MSG);
}

Server::Server(const Server &ref){
    *this = ref;
}

Server::~Server(){
        delete[] _buff;
};

Server &Server::operator=(const Server &ref){
    this->_buff = ref._buff;
    return (*this);
}


void Server::Listen(Socket sk, int backlog){
    if (listen(sk.GetFd(), backlog) < 0){
        perror("listen failed. Error:");
        exit(1);
    }
    else 
        std::cout << "listening on " << sk.GetIp() << ":" << sk.GetPort() << std::endl;
}

void Server::Select(Socket sk, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, struct timeval *timeout){
    if (select(sk.GetFd() + 1, &this->_readfs, writefds, exceptfds, timeout) < 0){
        perror("select failed. Error");
        exit(1);
    }
}

void Server::Accept(Socket sk){
    this->_csock = accept(sockfd, 
       reinterpret_cast<struct sockaddr *> (&myaddr), &len);
    if (this->_csock  < 0){
        perror("connection server failed. Error");
        exit (1);
    }                
    else {
        std::cout << "client " << this->_id++ << ": [" << inet_ntoa(sk._addr.sin_addr)
           << ":" << ntohs(sk._addr.sin_port) << "]" << std::endl;
    }
}

fd_set *Server::GetReadFs(){
    return (&this->_readfs);
}
