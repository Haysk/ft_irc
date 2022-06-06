#include "Socket.hpp"

Socket::Socket():
_addr(NULL),
_len(0){};

Socket::Socket(const Socket &ref){
    *this = &ref;
}

Socket::~Socket(){};



