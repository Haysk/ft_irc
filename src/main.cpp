#include "Socket.hpp"
#include "Server.hpp"
#include <csignal>
#include <sys/types.h>
#include <sys/socket.h>
#define LIMIT_MSG 512
#define LIMIT_PORT 65535


void signal_handler (int n){
    std::cerr<<std::endl;
    std::cerr << "Interruption by signal " << n << std::endl;
    throw std::invalid_argument("Force quit server");
}

bool is_num(char *s){
    while(*s){
        if(std::isdigit(*s) == 0)
            return (false);
        s++;
    }
    return (true);
}

int str_error(int ret, const char *str){
    std::cout << "Error: " << str;
   return (ret); 
}

bool check_input(int ac, char **av){
    int n = atoi(av[1]);

    if (ac != 3)
        return(str_error(0, "Wrong number of arguments\n"));
    else if (is_num(av[1]) == false)
        return (str_error(0, "2nd arg is not a number\n"));
    else if (n < 0 || n > LIMIT_PORT)
        return (str_error(0, "the highest TCP port number is 65 535\n"));
    return (true);
}

int main(int ac, char **av){

    if (check_input(ac, av) == false)
        return (0);
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
            // set master fd in fd_set
            FD_SET(sk._fd, &sk._readfs);
            sk._max_fd = sk._fd;
            // set client fd in fd_set
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