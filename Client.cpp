#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define ERROR_C "Client error: "
#define DEFUALT_PORT 1606
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

int main(){
    int client;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        std::cout<< ERROR_C << "esteblishing socket error";
        exit(0);
    }
    std::cout<< "Client: Socket for client was successfully created\n";

    server_address.sin_port = htons(DEFUALT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    int ret = connect(client, reinterpret_cast<struct sockaddr*>(&server_address),
                    sizeof(server_address));
    if(ret==0){
        std::cout<< "=> Connection to server "
                << inet_ntoa(server_address.sin_addr)
                << " with port number: "
                << DEFUALT_PORT << '\n';
    }



    char buffer[BUFFER_SIZE];
    /*
    std::cout<< "Waiting for server confirmation...\n";
    recv(client, buffer, BUFFER_SIZE, 0);
    
    std::cout<< "SERVER: ";
    recv(client, buffer, BUFFER_SIZE, 0);
    std::cout<< buffer;
    std::cout<< "Connection esteblished\n";
    */

    //отправка сообщения серверу
    std::cout<< "CLIENT: ";
    std::cin.getline(buffer, BUFFER_SIZE);
    send(client, buffer, BUFFER_SIZE, 0);



    //разрыв сооединения с сервером
    close(client);
    std::cout<< "END\n";

    return 0;
}
