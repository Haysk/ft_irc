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
        signal(SIGINT, signal_handler);
        sk.CreateFd(AF_INET, SOCK_STREAM, 0);
        sk.SetAddr(AF_INET);
        sk.Bind();
        sv.Listen(sk, 10);
        sk._max_fd = sk._fd;
        while(1){
            FD_ZERO(&sk._readfs);
            FD_SET(sk._fd, &sk._readfs);

            std::cout << "max_fd: " << sk._max_fd << std::endl;
            //waiting for a new client
            sv.Select(sk, 0);

            //connexion client
            if (FD_ISSET(sk._fd, &sk._readfs)){
                    sv.Accept(sk);
            //send
            for (int i = 0; i < sk._max_fd; i++){
                if (FD_ISSET(i, &sk._readfs)){
                    sv.Recv(i, 0);
                    memset(sv._buff, 0, LIMIT_MSG);
                }
            }
            // if (FD_ISSET(sv.GetFdMax()-1,sv.GetReadFs())){
                    // sv.Recv(sv.GetFdMax(), 0);
            //         memset(sv.GetBuff(), 0, LIMIT_MSG);
            //         std::cout << "3)" << std::endl;
            }
        }
    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // close(sv.GetClientSocket());
    return (0);
}