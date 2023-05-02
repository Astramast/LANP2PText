#include <iostream>
using std::cerr, std::endl;
#include "SocketHandler.hpp"
#include "config.hpp"

// Public methods

SocketHandler::SocketHandler(){
	createSocket();
}

// Private methods

void SocketHandler::createSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1){
		cerr << "Error : Impossible to create the socket" << endl;
		exit(-1);
	}
}

void SocketHandler::connect(const string& ip, const std::uint16_t& port){
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;

	return connect(sockfd, (struct sockaddr *)addr, sizeof(addr));
}

void SocketHandler::bindSocket(const std::uint16_t& port){
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		cerr << "Error : Impossible to link the socket" << endl;
		exit(-2);
	}
}

int SocketHandler::accept(){
	listen(sockfd, MAX_ENTERING_CONNECTION);
	int in_sockfd = accept(sockfd, addr, sizeof(addr));
	if (in_sockfd < 0){
		cerr << "Error : impossible to accept entering connection" << endl;
		exit(-3);
	}
	cout << "Entering connection accepted !" << endl;
	return in_sockfd;
}

