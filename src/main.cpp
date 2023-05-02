#include <iostream>
using std::cout, std::endl, std::cin;
#include <string>
using std::string, std::stoi;
#include <exception>
using std::exception;
#include "SocketHandler.hpp"

string input(const string& message){
	string input;
	cout << message;
	getline(cin, input);
	return input;
}

uint16_t port_input(const string& message){
	uint16_t input_number=0;
	bool flag = true;
	
	while(flag){
		string input_ = input(message);
		try{
			input_number = stoi(input_);
		}
		catch (const exception& e){
			cout << "That was not a valid integer, please try again." << endl;
			continue;
		}
		flag = false;
	}
	return static_cast<std::uint16_t>(input_number);
}

int main(int argc, char *argv[]){
	std::uint16_t port = port_input("Enter a local port (>1024) : ");
	
	SocketHandler socket(port);
	string ip = input("Enter corresponding ip : ");
	std::uint16_t corr_port = port_input("Enter corresponging port : ");
	
	socket.connect(ip, corr_port);


    int valread = read(client_sockfd, buffer, 1024); // Lire les données envoyées par le client
    cout << "Data received : " << buffer << endl;

    close(client_sockfd);
    close(sockfd);

    return 0;
}

