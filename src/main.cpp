#include "Socket.hpp"
#include "Server.hpp"
#include <csignal>
#define LIMIT_MSG 512

#include <sys/types.h>
#include <sys/socket.h>


void signal_handler (int n){
    std::cerr<<std::endl;
    std::cerr << "Interruption by signal " << n << std::endl;
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
        sv.Listen(&sk, 10);
        while(1){
            FD_ZERO(&sk._readfs);
            FD_SET(sk._fd, &sk._readfs);
            sk._max_fd = sk._fd;
            for(size_t i = 0; i < sk._client.size(); i++){
                FD_SET(sk._client[i], &sk._readfs);

                if (sk._client[i] > sk._max_fd)
                    sk._max_fd = sk._client[i];
            }

            //waiting for a new client
            sv.Select(&sk, 0);

            //connexion client
            if (FD_ISSET(sk._fd, &sk._readfs))
                sv.Accept(&sk);

            //check clients activity
            for (size_t i = 0; i < sk._client.size(); i++){
                if (FD_ISSET(sk._client[i], &sk._readfs)){
                    sv.Recv(&sk, i, 0);
                    memset(sv._buff, 0, LIMIT_MSG);
                }
            }
            
        }
    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return (0);
}