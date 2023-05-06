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
	std::uint16_t local_port = port_input("Enter a local port (>1024) : ");
	string remote_ip = input("Enter remote ip : ");
	std::uint16_t remote_port = port_input("Enter remote port : ");
	
	SocketHandler socket(local_port, remote_port, remote_ip);
	
	string useless = input("fin main : ");
    return 0;
}

