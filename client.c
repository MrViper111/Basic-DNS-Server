#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "util.h"

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
#define CACHE_PATH "cache.txt"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    
    connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr));
    printf("Connected to server\n");
    
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE];
    
    while (1) {
        printf("> ");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';
        
        if (strlen(command) == 0) {
            continue;
        }

        if (strcmp(command, "clearcache") == 0) {
            wipe(CACHE_PATH);
            printf("Cleared existing cache.\n");

            continue;
        }
        
        send(sock, command, strlen(command), 0);
        
        memset(buffer, 0, BUFFER_SIZE);
        int bytes = read(sock, buffer, BUFFER_SIZE);
        
        if (bytes <= 0) {
            printf("Server disconnected\n");
            break;
        }
        
        printf("%s\n", buffer);

        // add cache later
    }
    
    close(sock);
    return 0;
}
