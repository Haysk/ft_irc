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


void Server::Listen(Socket *sk, int backlog){
    if (listen(sk->_fd, backlog) < 0)
        throw Server::ListenFailed();
    else 
        std::cout << "listening on " << sk->_ip << ":" << sk->_port << std::endl;
}

void Server::Select(Socket *sk, struct timeval *timeout){

    if (select(sk->_max_fd + 1, &sk->_readfs, 0, 0, timeout) < 0)
        throw Server::SelectFailed();
}

void Server::Accept(Socket *sk){
    socklen_t len;
    int fd = accept(sk->_fd, 
    reinterpret_cast<struct sockaddr *>(&sk->_addr), &len);
    if (fd < 0){
        std::cout << "fd " << fd << "failed" << std::endl;
    }
    else {
        std::cout << "== client " << this->_id++ << " =="<< std::endl;
        std::cout << "addres: [" << inet_ntoa(sk->_addr.sin_addr)
        << ":" << ntohs(sk->_addr.sin_port) << "]" << std::endl;
        std::cout << "fd: " << fd << std::endl ;
        sk->_client.push_back(fd);
    }
}

void Server::Recv(Socket *sk, int i, int flag){
    int ret;
    if ((ret = recv(sk->_client[i], this->_buff, LIMIT_MSG, flag)) > 0)
        std::cout << "client send:" << this->_buff << std::endl;
    else if (ret == 0){
        std::cout << "fd " << sk->_client[i]<< " disconnected" << std::endl;
        sk->_client.erase(sk->_client.begin() + i);
    }
    else 
        std::cout << "fd " << sk->_client[i] << " recv return: " << ret << std::endl;
    
}

const char *Server::ListenFailed::what()const throw(){
    return ("Listen failed");
}

const char *Server::SelectFailed::what()const throw(){
    return ("Select failed");
}
