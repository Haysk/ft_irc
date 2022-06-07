#include "Socket.hpp"

Socket::Socket(const char *ip, int port):
_ip(ip),
_port(port),
_fd(-1){};

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

    if (sockfd < 0){
        perror("socket failed. Error:");
        exit(1);
    }
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

    if (bind(this->_fd, cast_addr, sizeof(this->_addr)) < 0){
        perror("bind failed. Error");
        exit (1);
    }

}

int Socket::GetFd()const{
    return (this->_fd);
}

int Socket::GetPort()const{
    return (this->_port);
}

const char *Socket::GetIp(){
    return (this->_ip);
}

struct sockaddr_in *Socket::GetAddr(){
    return (&this->_addr);
}

