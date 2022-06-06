#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <functional>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#define IP "127.0.0.1"
#define LIMIT_MSG 512

int main(int ac, char **av){
    struct sockaddr_in myaddr;
    socklen_t len;
    int sockfd, csock;
    fd_set readfs;
    int id = 0;

    if (ac != 3){
        std::cout << "Wrong input" << std::endl;
        std::cout << "note: ./ircserv <port> <password>" << std::endl;
        return (0);
    }
    /* [1] == SOCKET SERVER == */
    /* [1.a] Create socket server*/
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket failed. Error");
        exit(1);
    }

    /* [1.b] Initialize myaddr*/

    bzero(reinterpret_cast<struct sockadrr *> (&myaddr), sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = inet_addr(IP);
    myaddr.sin_port = htons(atoi(av[1]));

    /* [1.c] Bind socket fd and sockeadrr_in */

    if (bind(sockfd, reinterpret_cast<struct sockaddr *> (&myaddr), sizeof(myaddr)) < 0){
        perror("bind failed. Error");
        exit (1);
    }

    /* [2] == LAUNCH SERVER == */
    /* [2.a] Listen on sockfd */

        if (listen(sockfd, 10) == -1){ //how many connexion
            perror("listen failed. Error");
            exit(1);
        }
        else
            std::cout << "listening on [" << IP << ":" << atoi(av[1]) << "] ..." << std::endl;

    /* [2.b] Select socket */

        char *buff = new char[LIMIT_MSG];
        int r;
        while(1) {
            FD_ZERO(&readfs);
            FD_SET(sockfd, &readfs);
            if (select(sockfd + 1, &readfs, NULL, NULL, NULL) < 0){
                perror("select failed. Error");
                exit(1);
            }
            memset(buff, 0, LIMIT_MSG);
            buff[LIMIT_MSG] = '\0';
            if (FD_ISSET(sockfd, &readfs)){
    /* [2.c] Accept socket */
                if ((csock = accept(sockfd, 
                    reinterpret_cast<struct sockaddr *> (&myaddr), &len)) < 0){
                       perror("connection server failed. Error");
                      exit (1);
                 }
                else {
                     std::cout << "client " << id++ << ": [" << inet_ntoa(myaddr.sin_addr)
                        << ":" << ntohs(myaddr.sin_port) << "]" << std::endl;
                }
                    if ((r = recv(csock, buff, LIMIT_MSG, 0)) < 0){
                       perror("connection server failed. Error");
                    }
                    else {
                        std::cout << "r: " << r << std::endl;
                        std::cout << "client send:" << buff << std::endl;
                    }
                    if (send(csock, "CAP * LS",4, 0) < 0){
                        perror("send failed . Error");
                        exit(1);
                    }

                    close(csock);
            }
        }
        delete[] buff;
    return (0);
}