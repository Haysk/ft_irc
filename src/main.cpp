#include "Socket.hpp"

int main(int ac, char **av){

    Socket s;

    if (ac != 3){
        std::cout << "Wrong input" << std::endl;
        std::cout << "note: ./ircserv <port> <password>" << std::endl;
        return (0);
    }

    s.CreateFd(AF_INET, SOCK_STREAM, 0);
    s.SetAddr(AF_INET, "127.0.0.1", atoi(av[1]));
    s.Bind(s.GetFd(), s.GetAddr());
    return (0);
}