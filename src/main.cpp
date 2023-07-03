#include <iostream>
using std::cout, std::endl, std::cin;
#include <string>
using std::string, std::stoi;
#include <exception>
using std::exception;
#include <thread>
using std::thread;
#include <cstring>
using std::memset;
#include <memory>
using std::shared_ptr, std::make_shared;
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

void writeAndSend(shared_ptr<SocketHandler> socket){
	while(socket->isopen()){
		string message = input("");
		if (message == "/exit"){
			break;
		}
		int n = message.length()/1023;
		for(int i=0; i<n+1; i++){
			std::string msg = message.substr(i*1023, 1023);
			char buffer[1024];
			copy(msg.begin(), msg.end(), buffer);
			buffer[msg.size()] = '\0';
			socket->sockwrite(buffer);
			memset(buffer, 0, sizeof(buffer));
		}
	}
	socket->close();
}

void readAndPrint(shared_ptr<SocketHandler> socket){
	char buffer[1024];
	while(socket->isopen()){
		if(socket->sockread(buffer)){
			cout << buffer << endl;
		}
		else{break;}
	}
}

int main(){
	std::uint16_t local_port = port_input("Enter a local port (>1024) : ");
	string remote_ip = input("Enter remote ip : ");
	std::uint16_t remote_port = port_input("Enter remote port : ");
	
	shared_ptr<SocketHandler> socket = make_shared<SocketHandler>(local_port, remote_port, remote_ip);
	
	thread in(readAndPrint, socket);
	thread out(writeAndSend, socket);

	in.join();
	out.join();
	
	string useless = input("fin main : "); //TODO Remove
    return 0;
}

