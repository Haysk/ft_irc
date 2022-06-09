#include "Socket.hpp"
#include "Server.hpp"
#include <csignal>
#define LIMIT_MSG 512


void signal_handler (int n){
    std::cerr<<std::endl;
    std::cerr << "interruption by signal " << n << std::endl;
    throw std::invalid_argument("Force quit server");
}

int main(int ac, char **av){
    if (ac != 3){
        std::cout << "Wrong input" << std::endl;
        std::cout << "note: ./ircserv <port> <password>" << std::endl;
        return (0);
    }
    Socket sk("127.0.0.1", atoi(av[1]));
    Server sv;
    try {
        sk.CreateFd(AF_INET, SOCK_STREAM, 0);
        sk.SetAddr(AF_INET);
        sk.Bind();
        sv.Listen(sk, 10);
        while(sv.GetId() < 10){
            signal(SIGINT, signal_handler);
            FD_ZERO(sv.GetReadFs());
            FD_SET(sk.GetFd(), sv.GetReadFs());
            //change 1st param of select
            sv.Select(sk, sv.GetReadFs(), 0, 0, 0);
            //connexion
            if (FD_ISSET(sk.GetFd(), sv.GetReadFs())){
                sv.Accept(sk);
            }
            //send 
            // check if enter
            if (FD_ISSET(sv.GetFdMax(),sv.GetReadFs())){
                memset(sv.GetBuff(), 0, LIMIT_MSG);
                sv.Recv(sv.GetFdMax(), 0);
            }
        }
    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // close(sv.GetClientSocket());
    return (0);
}