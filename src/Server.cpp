#include "Server.hpp"
#include "Socket.hpp"

Server::Server(){}

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