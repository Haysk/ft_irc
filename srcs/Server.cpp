#include "../includes/Server.hpp"
#include "../includes/Socket.hpp"
#include "../includes/tester.hpp"
#define LIMIT_MSG 512

Server::Server(){
    this->_buff = new char[LIMIT_MSG];
    memset(this->_buff, 0, LIMIT_MSG);
}

Server::Server(const Server &ref){
    *this = ref;
}

Server::~Server(){
        delete[] _buff;
};

Server &Server::operator=(const Server &ref){
    this->_buff = ref._buff;
    return (*this);
}


void Server::Listen(Socket *sk, int backlog){
    if (listen(sk->_fd, backlog) < 0)
        throw Server::ListenFailed();
    else{
        std::cout << MAGENTA << "Listening on [" << sk->_ip << ":";
        std::cout << sk->_port << "] ..." << RESET << std::endl;
    }
}

void Server::Select(Socket *sk, struct timeval *timeout){

    if (select(sk->_max_fd + 1, &sk->_readfs, 0, 0, timeout) < 0)
        throw Server::SelectFailed();
}

void Server::Accept(Datas &servDatas, Socket *sk){
    socklen_t len = 0;
    int fd = accept(sk->_fd, 
    reinterpret_cast<struct sockaddr *>(&sk->_addr), &len);
    if (fd < 0)
        std::cout << "fd " << fd << "failed" << std::endl;
    else {
        std::cout << BOLDGREEN << "client fd " << fd <<": connected"<< RESET << std::endl;
        sk->_client.push_back(fd);
	servDatas.displayServLogo(fd);
	sendMsgToClient(fd, "Welcome to my MY-IRC !");
	sendMsgToClient(fd, "Enter CAP LS to continue:");
	servDatas.newUser(fd);
	//servDatas.sendPrompt(fd);
    }
}

void Server::Recv(Datas &servDatas, Socket *sk, int i, int flag){
    int ret;

    if ((ret = recv(sk->_client[i], this->_buff, LIMIT_MSG, flag)) > 0){
	    std::string	cmd = std::string(this->_buff);
		std::cout << "Client send: " << cmd << std::endl;
	    try
	    {
	    	servDatas.treatCmds(sk->_client[i], cmd);
	    } catch (datasException &e) {
			stringstream ss;
			ss << "ircserv " << e.getOption() << " " << e.what();
			sendMsgToClient(sk->_client[i], ss.str());
		} catch (std::exception &e) {
			sendMsgToClient(sk->_client[i], "ircserv " + string(e.what()));
		}
	    if (!servDatas.getUser(sk->_client[i]).getCo())
	    {
        	std::cout << BOLDRED << "client fd " << sk->_client[i]<< ": disconnected"<< RESET << std::endl;
		servDatas.disconnectUser(servDatas.getUser(sk->_client[i]));
		close(sk->_client[i]);
        	sk->_client.erase(sk->_client.begin() + i);
		return ;
	    }
    }
    else if (ret == 0) {
        std::cout << BOLDRED << "client fd " << sk->_client[i]<< ": disconnected"<< RESET << std::endl;
	servDatas.disconnectUser(servDatas.getUser(sk->_client[i]));
	close(sk->_client[i]);
        sk->_client.erase(sk->_client.begin() + i);
    }
    else
        std::cout << "fd " << sk->_client[i] << " recv return: " << ret << std::endl;
}

const char *Server::ListenFailed::what()const throw(){
    return ("Listen failed");
}

const char *Server::SelectFailed::what()const throw(){
    return ("Select failed");
}
