#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CONNECTIONS=1

using namespace std;

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error : impossible to create the socket" << endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port de communication
    server_addr.sin_addr.s_addr = INADDR_ANY; // Adresse IP locale

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error : impossible to link the socket" << endl;
        return -2;
    }

    listen(sockfd, MAX_CONNECTIONS); // Le socket écoute jusqu'à 5 connexions entrantes

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

