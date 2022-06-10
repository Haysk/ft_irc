#include "Server.hpp"
#include "Socket.hpp"
#define LIMIT_MSG 512


Server::Server():
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
    if (listen(sk._fd, backlog) < 0)
        throw Server::ListenFailed();
    else 
        std::cout << "listening on " << sk._ip << ":" << sk._port << std::endl;
}

void Server::Select(Socket sk, struct timeval *timeout){
    std::cout << "in select" << std::endl;
    if (select(sk._max_fd + 1, &sk._readfs, 0, 0, timeout) < 0)
        throw Server::SelectFailed();
    else {
        sk._max_fd++;
        std::cout << "max_fd: " << sk._max_fd << std::endl;
    }
}

void Server::Accept(Socket sk){
    socklen_t len;
    int fd = accept(sk._fd, 
       reinterpret_cast<struct sockaddr *> (&sk._addr), &len);

    if (fd < 0){
        std::cout << "fd " << fd << "failed" << std::endl;
    }
    else {
        std::cout << "== client " << this->_id++ << " =="<< std::endl;
        std::cout << "addres: [" << inet_ntoa(sk._addr.sin_addr)
        << ":" << ntohs(sk._addr.sin_port) << "]" << std::endl;
        std::cout << "fd: " << fd << std::endl;
    }
}

void Server::Recv(int fd, int flag){
    if (recv(fd, this->_buff, LIMIT_MSG, flag) > 0)
        std::cout << "client send:" << this->_buff << std::endl;
}

const char *Server::ListenFailed::what()const throw(){
    return ("Listen failed");
}

const char *Server::SelectFailed::what()const throw(){
    return ("Select failed");
}
