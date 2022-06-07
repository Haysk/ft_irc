#include "Socket.hpp"

Socket::Socket():
_fd(-1){}

Socket::Socket(const Socket &ref){
    *this = ref;
}

Socket &Socket::operator=(const Socket &ref){
    this->_addr = ref._addr;
    this->_fd = ref._fd;
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


void Socket::SetAddr(int domain,const char *ip, int port){
    bzero(reinterpret_cast<struct sockadrr *>(&this->_addr)
    , sizeof(this->_addr));
    this->_addr.sin_family = domain;
    this->_addr.sin_addr.s_addr = inet_addr(ip);
    this->_addr.sin_port = htons(port);
}

void Socket::Bind(int sockfd, struct sockaddr_in *addr){
    struct sockaddr *cast_addr = reinterpret_cast<struct sockaddr *>(addr);

    if (bind(sockfd, cast_addr, sizeof(*addr)) < 0){
        perror("bind failed. Error");
        exit (1);
    }

}

int Socket::GetFd()const{
    return (this->_fd);
}


struct sockaddr_in *Socket::GetAddr(){
    return (&this->_addr);
}
