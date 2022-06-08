#include "Server.hpp"
#include "Socket.hpp"
#define LIMIT_MSG 512


Server::Server():
_csock(-1),
_id(0){
    this->_buff = new char[LIMIT_MSG];
    memset(this->_buff, 0, LIMIT_MSG);
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
    if (select(sk.GetFd() + 1, readfds, writefds, exceptfds, timeout) < 0){
        perror("select failed. Error");
        exit(1);
    }
}

void Server::Accept(Socket sk){
    socklen_t len;
    this->_csock = accept(sk.GetFd(), 
       reinterpret_cast<struct sockaddr *> (sk.GetAddr()), &len);

    if (this->_csock  < 0){
        perror("connection server failed. Error");
        exit (1);
    }                
    else {
        std::cout << "client " << this->_id++ << ": [" << inet_ntoa(sk.GetAddr()->sin_addr)
           << ":" << ntohs(sk.GetAddr()->sin_port) << "]" << std::endl;
    }
}

void Server::Recv(int flag){
    if (recv(this->_csock, this->_buff, LIMIT_MSG, flag) < 0){
       perror("connection server failed. Error");
    }
    else {
        std::cout << "client send:" << this->_buff << std::endl;
    }
}

int Server::GetClientSocket(){
    return (this->_csock);
}

fd_set *Server::GetReadFs(){
    return (&this->_readfs);
}

int Server::GetId(){
    return (this->_id);
}