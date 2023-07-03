#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
using std::cerr, std::endl, std::cout;
#include "SocketHandler.hpp"

// Constructors

SocketHandler::SocketHandler(const std::uint16_t& local_port, const std::uint16_t& remote_port, const string& remote_ip){
	//Remote adress
	addr_there.sin_family = AF_INET;
	addr_there.sin_port = htons(remote_port);
	addr_there.sin_addr.s_addr = inet_addr(remote_ip.c_str());
	//Local adress
	addr_here.sin_family = AF_INET;
	addr_here.sin_port = htons(local_port);
	addr_here.sin_addr.s_addr = INADDR_ANY;
	//init P2P procedure
	createSocket();
	bind();
	if (!connect()){
		accept();
	}
}

// Public methods

bool SocketHandler::sockread(char buffer[1024]){
	std::uint16_t i = 0;
	ssize_t written = 0;
	while (i<1024){
		written = recv(sockfd, buffer, 1024-i, 0);
		if (written < 0){
			cerr << "Error while receiving information." << endl;
			exit(errno);
		}
		if (written == 0){
			cout << "Peer disconnected. Disconnecting..." << endl;
			::close(sockfd);
			return false;
		}
		i += written;
	}
	return true;
}

void SocketHandler::sockwrite(const char buffer[1024]){
	if (send(sockfd, buffer, 1024, 0) < 0){
		cerr << "Error while sending information." << endl;
		exit(errno);
	}
}

bool SocketHandler::isopen(){
	return is_open;
}

void SocketHandler::close(){
	is_open = false;
	::close(sockfd);
}

// Private methods

void SocketHandler::createSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1){
		cerr << "Error : Impossible to create the socket" << endl;
		exit(errno);
	}
}

void SocketHandler::bind(){
	socklen_t size = sizeof(addr_here);
	if (::bind(sockfd, (struct sockaddr *)&addr_here, size) < 0){
		cerr << "Error : Impossible to link the socket" << endl;
		exit(errno);
	}
}

bool SocketHandler::connect(){
	socklen_t size = sizeof(addr_there);
	if (::connect(sockfd, (struct sockaddr *)&addr_there, size) < 0 ){
		if (errno == ECONNREFUSED){
			cout << "Connection refused, accepting connections..." << endl;
		}
		else{
			cout << "Error : Connection failed." << endl;
			exit(errno);
		}
		return false;
	}
	return true;
}

void SocketHandler::accept(){
	listen(sockfd, 1);
	bool flag = true;
	while (flag){
		struct sockaddr_in accepted_addr;
		socklen_t size = sizeof(accepted_addr);
		int in_sockfd = ::accept(sockfd, (struct sockaddr *)&accepted_addr, &size);
		if (in_sockfd < 0){
			cerr << "Error : impossible to accept entering connection" << endl;
			exit(errno);
		}
		if ((accepted_addr.sin_port == addr_there.sin_port) && (accepted_addr.sin_addr.s_addr == addr_there.sin_addr.s_addr)){
			sockfd = in_sockfd;
			flag = false;
		}
		else{
			cout << "Wrong connection attempted." << endl;
			::close(in_sockfd);
		}
	}
	cout << "Entering connection accepted !" << endl;
}

