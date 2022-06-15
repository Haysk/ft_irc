#include "../includes/Socket.hpp"

Socket::Socket(const char *ip, int port):
_ip(ip),
_port(port),
_max_fd(0),
_fd(0){};

Socket::Socket(const Socket &ref){
    *this = ref;
}

Socket &Socket::operator=(const Socket &ref){
    this->_addr = ref._addr;
    this->_fd = ref._fd;
    this->_ip = ref._ip;
    this->_port = ref._port;
    return (*this);
}

Socket::~Socket(){};

void Socket::CreateFd(int domain, int type, int protocol){
    int sockfd = socket(domain, type, protocol);

    if (sockfd < 0)
        throw Socket::SocketFailed();
    this->_fd = sockfd;
};


void Socket::SetAddr(int domain){
    bzero(reinterpret_cast<struct sockadrr *>(&this->_addr)
    , sizeof(this->_addr));
    this->_addr.sin_family = domain;
    this->_addr.sin_addr.s_addr = inet_addr(this->_ip);
    this->_addr.sin_port = htons(this->_port);
}

void Socket::Bind(){
    struct sockaddr *cast_addr = reinterpret_cast<struct sockaddr *>(&this->_addr);
    if (bind(this->_fd, cast_addr, sizeof(this->_addr)) < 0)
        throw Socket::BindFailed();

}


const char *Socket::SocketFailed::what()const throw(){
    return ("Socket failed");
}

const char *Socket::BindFailed::what()const throw(){
    return ("Bind failed");
}
