#include "Socket.hpp"
#include "Server.hpp"
#include <csignal>


void signal_handler (int n){
    std::cerr<<std::endl;
    std::cerr << "interruption by signal " << n << std::endl;
    throw std::invalid_argument("Force quit server");
}

int main(int ac, char **av){

    std::string input;
    Socket sk("127.0.0.1", atoi(av[1]));
    Server sv;

    if (ac != 3){
        std::cout << "Wrong input" << std::endl;
        std::cout << "note: ./ircserv <port> <password>" << std::endl;
        return (0);
    }
    try {

        sk.CreateFd(AF_INET, SOCK_STREAM, 0);
        sk.SetAddr(AF_INET);
        sk.Bind();
        sv.Listen(sk, 10);
        while(sv.GetId() < 10){
            signal(SIGINT, signal_handler);
            FD_ZERO(sv.GetReadFs());
            FD_SET(sk.GetFd(), sv.GetReadFs());
            sv.Select(sk, sv.GetReadFs(), 0, 0, 0);
            if (FD_ISSET(sk.GetFd(), sv.GetReadFs())){
                sv.Accept(sk);
                sv.Recv(0);
                close(sv.GetClientSocket());
            }
        }
    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return (0);
}