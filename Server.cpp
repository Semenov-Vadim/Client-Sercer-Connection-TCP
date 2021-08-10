#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <cstring>

#define ERROR_S "Server error: "
#define DEFUALT_PORT 1606
#define BUFFER_SIZE 1024
//#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

int main(){
    int client, server;
    struct sockaddr_in server_address;


    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        std::cout<< ERROR_S << "esteblishing socket error.";
        exit(0);
    }
    std::cout<< "SERVER: Socket for server was successfully created\n";




    server_address.sin_port = htons(DEFUALT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address),
                    sizeof(server_address));
    if(ret<0){
        std::cout<< ERROR_S
        << "binding connection. Socket has already been esteblished.\n";
        return -1;
    }

    socklen_t size = sizeof(server_address);
    std::cout<< "SERVER: listening client...\n";
    listen(client, 1);

    server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    if(server < 0){
        std::cout<< ERROR_S << "Can`t accept client";
    }



    char buffer[BUFFER_SIZE];
    /*
    //strcpy(buffer, "Server connected!\n");
    //send(server,buffer, BUFFER_SIZE, 0);
    std::cout<< "=>Connected to the client\n";
    //std::cout <<"send '" << CLIENT_CLOSE_CONNECTION_SYMBOL << "' to close the connection";
    */

    //принимаем сообщение от клиента
    std::cout<< "CLIENT: ";
    recv(server, buffer, BUFFER_SIZE, 0);
    std::cout<< buffer <<'\n';

/*
    std::cout<<"SERVER: ";
    std::cin.getline(buffer, BUFFER_SIZE);
    send(server, buffer, BUFFER_SIZE, 0);

    std::cout<< "CLIENT:";
    recv(server, buffer, BUFFER_SIZE, 0);
    std::cout<< buffer << '\n';
*/

    std::cout<< "END\n";
    return 0;
}
