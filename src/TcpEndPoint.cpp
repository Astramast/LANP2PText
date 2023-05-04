#include <iostream>
using std::cerr, std::endl, std::cout;
#include "TcpEndPoint.hpp"
#include "config.hpp"

// Constructors

TcpEndPoint::TcpEndPoint(){
	createSocket();
}

// Public methods

bool TcpEndPoint::connect(const string& ip, const std::uint16_t& port){
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;

	if (connect(sockfd, addr, (socklen_t)sizeof(*addr)) < 0){
		if (errno == ECONNREFUSED){
			cout << "Connection failed." << endl;
		}
		return false;
	}
	return true;
}

void TcpEndPoint::bindSocket(const std::uint16_t& port){
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		cerr << "Error : Impossible to link the socket" << endl;
		exit(-2);
	}
}

int TcpEndPoint::accept(){
	listen(sockfd, MAX_ENTERING_CONNECTION);
	int in_sockfd = accept(sockfd, addr, sizeof(addr));
	if (in_sockfd < 0){
		cerr << "Error : impossible to accept entering connection" << endl;
		exit(-3);
	}
	cout << "Entering connection accepted !" << endl;
	return in_sockfd;
}

// Private methods

void TcpEndPoint::createSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;

	if (sockfd == -1){
		cerr << "Error : Impossible to create the socket" << endl;
		exit(-1);
	}
}
