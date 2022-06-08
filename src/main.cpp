#include "Socket.hpp"
#include "Server.hpp"

int main(int ac, char **av){

    Socket sk("127.0.0.1", atoi(av[1]));
    Server sv;

    if (ac != 3){
        std::cout << "Wrong input" << std::endl;
        std::cout << "note: ./ircserv <port> <password>" << std::endl;
        return (0);
    }
    sk.CreateFd(AF_INET, SOCK_STREAM, 0);
    sk.SetAddr(AF_INET);
    sk.Bind();
    sv.Listen(sk, 10);
    while(1){
        FD_ZERO(sv.GetReadFs());
        FD_SET(sk.GetFd(), sv.GetReadFs());
        sv.Select(sk, sv.GetReadFs(), 0, 0, 0);
        if (FD_ISSET(sk.GetFd(), sv.GetReadFs())){
            sv.Accept(sk);
        }
    }
    return (0);
}