#include <stdio.h>
// printf
#include <string.h>
// strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>
int main(int argc, char *argv[])
{
    int sock,recieve_size;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    server.sin_addr.s_addr = inet_addr("192.168.8.187");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    puts("Connected\n");
    while (1)
    {
        printf("Enter message : ");
        scanf("%s", message);
        // Send some data
        if (send(sock, message, strlen(message), 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts("Server reply :");
        puts(server_reply);
        memset(message,'\0',1000);
        memset(server_reply,'\0',2000);
    }
    close(sock);
    return 0;
}