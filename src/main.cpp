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
        FD_ZERO(sv.GetReadFs());
        FD_SET(sk.GetFd(), sv.GetReadFs());
        while(1){
            signal(SIGINT, signal_handler);

            //waiting for a new client
            sv.Select(FD_SETSIZE, sv.GetReadFs(), 0, 0, 0);

            //connexion client
            for (int i = 0; i < FD_SETSIZE; i++){
                if (FD_ISSET(i, sv.GetReadFs()))
                    sv.Accept(sk);
            }
            //send
            // if (FD_ISSET(sv.GetFdMax()-1,sv.GetReadFs())){
                    // sv.Recv(sv.GetFdMax(), 0);
            //         memset(sv.GetBuff(), 0, LIMIT_MSG);
            //         std::cout << "3)" << std::endl;
            // }
        }
    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // close(sv.GetClientSocket());
    return (0);
}