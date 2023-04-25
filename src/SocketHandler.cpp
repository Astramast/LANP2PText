#include "SocketHandler.hpp"
#include <iostream>
using std::cerr, std::endl;

// Public methods

SocketHandler::SocketHandler(std::uint16_t port){
	createSocket();
	bindSocket(port);
}

// Private methods

void SocketHandler::createSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1){
		cerr << "Error : Impossible to create the socket" << endl;
		exit(-1);
	}
}

void SocketHandler::bindSocket(std::uint16_t& port){
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		cerr << "Error : Impossible to link the socket" << endl;
		exit(-2);
	}
}

