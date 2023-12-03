/*
###########################################################
#### Fazendo um servidor Web minimalista em C no Linux ####
#### Criado em: 02/12/2023                             ####
#### Revisão  : 00                                     ####
#### Copyright (c) 2021 by Alan Lopes                  ####
###########################################################
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>

void main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        AF_INET,
        0x901f, // port number 8080
        0 // IPv4 address
    };
    
    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    // GET /<filename>.html
    char *f = buffer + 5;
    *strchr(f, ' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    sendfile(client_fd, opened_fd, 0, 256);
    close(opened_fd);
    close(client_fd);
    close(s);
}