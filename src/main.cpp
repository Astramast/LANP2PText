#include <iostream>
using std::cout, std::endl, std::cin;
#include <string>
using std::string, std::stoi;
#include <exception>
using std::exception;
#include "SocketHandler.hpp"

uint16_t port_input(const string& message){
	int input_number=0;
	bool flag = true;
	
	while(flag){
		cout << message;
		string input;
		getline(cin, input);
		try{
			input_number = stoi(input);
		}
		catch (const exception& e){
			cout << "That was not a valid integer, please try again." << endl;
			continue;
		}
		if (input_number < 0){
			cout << "Negative value entered. Exiting program..." << endl;
			exit(0);
		}
		if (input_number > 65535){
			cout << "This number is too big, enter a value between 0 and 65535." << endl;
			continue;
		}
		flag = false;
	}
	return static_cast<std::uint16_t>(input_number);
}

int main(int argc, char *argv[]){
	std::uint16_t port = port_input("Enter a port (0 to 65535, <0 value to quit) : ");
	
	SocketHandler socket(port);

    listen(sockfd, 1); // Le socket écoute jusqu'à 1 connexions entrantes

    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len); // Accepter une connexion entrante
    if (client_sockfd < 0) {
        cerr << "Error : impossible to accept entering connection" << endl;
        return -3;
    }

    cout << "Entering connection accepted !" << endl;

    char buffer[1024] = {0};
    int valread = read(client_sockfd, buffer, 1024); // Lire les données envoyées par le client
    cout << "Data received : " << buffer << endl;

    close(client_sockfd);
    close(sockfd);

    return 0;
}	

