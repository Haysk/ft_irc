#include "../includes/Socket.hpp"
#include "../includes/Server.hpp"
#include "../includes/Datas.hpp"
#include <csignal>
#include <sys/types.h>
#include <sys/socket.h>
#define LIMIT_MSG 512
#define LIMIT_PORT 65535

int main(int ac, char **av){

    if (check_input(ac, av) == false)
        return (0);
    std::string pwd = std::string(av[2]);
    Datas *servDatas;
    try {
        servDatas = new Datas(pwd);
    } catch (exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }
    Socket sk("127.0.0.1", atoi(av[1]));
    Server sv;
    try {
        signal(SIGINT, signal_handler);
        sk.CreateFd(AF_INET, SOCK_STREAM, 0);
        sk.SetAddr(AF_INET);
        sk.Bind();
        sv.Listen(&sk, 10);
        while (servDatas->getCo()){
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
                sv.Accept(*servDatas, &sk);

            //check clients activity
            for (size_t i = 0; i < sk._client.size(); i++){
                if (FD_ISSET(sk._client[i], &sk._readfs)){
                    sv.Recv(*servDatas, &sk, i, 0);
                    memset(sv._buff, 0, LIMIT_MSG);
                }
            }
        }
    }
    catch (std::exception &e){
	sk.closeClientFd();
        std::cerr << "ircserv: " << e.what() << std::endl;
    }
    delete servDatas;
    close(3);
    return (0);
}

/* Utils */

void signal_handler (int n){
    std::cerr<<std::endl;
    std::cerr << "Interruption by signal " << n << std::endl;
    throw std::invalid_argument("Quit server");
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
    if (ac != 3)
        return(str_error(0, "Wrong number of arguments\n"));
    int n = atoi(av[1]);
    if (is_num(av[1]) == false)
        return (str_error(0, "2nd arg is not a number\n"));
    else if (is_num(av[1]) == false)
        return (str_error(0, "first arg is not a number\n"));
    else if (n < 0 || n > LIMIT_PORT)
        return (str_error(0, "the highest TCP port number is 65 535\n"));
    return (true);
}
