#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA_IN struct sockaddr_in
#define SA struct sockaddr



int check(int exp,const char *msg){
    if(exp == -1){
        perror(msg);
        exit(1);
    }
    return exp;
}

int setup_server(int port,int backlog){
    int server_socket,client_socket,addr_size;
    SA_IN server_addr;

    check((server_socket = socket(AF_INET,SOCK_STREAM,0)),"Failed to create socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    check(bind(server_socket,(SA*)&server_addr,sizeof(server_addr)),"Bind Failed!");
    check(listen(server_socket,backlog),"Listen Failed!");

    return server_socket;
}

int accept_new_connection(int server_socket){
    int addr_size = sizeof(SA_IN);
    int client_socket;
    SA_IN client_addr;

    check(client_socket = accept(server_socket,(SA*)&client_addr,(socklen_t*)&addr_size),"accept failed");

    return client_socket;
}

void handle_connection(int client_socket){
    char buffer[BUFSIZ];
    size_t bytes_read;
    int msgsize = 0;

    while((bytes_read = read(client_socket,buffer+msgsize,sizeof(buffer)-msgsize))){
        msgsize += bytes_read;
        if(buffer[msgsize-1] == '\n') break;
    }

    send(client_socket,"HTTP/1.1 200 OK\r\n\r\n<html>\n\r<body>\n\r\rhello\n\r</body>\n</html>",strlen("HTTP/1.1 200 OK\r\n\r\n<html>\n\r<body>\n\r\rhello\n\r</body>\n</html>"),0);
    printf("connected");
    buffer[msgsize-1] = 0;

    printf("Request :%s\n",buffer);
    close(client_socket);
}


int main(){
    int server_socket = setup_server(PORT,5);
    
    while(1){

        printf("Waiting for the connections...\n");

        int client_socket = accept_new_connection(server_socket);
        handle_connection(client_socket);
    }

    return 0;
}


