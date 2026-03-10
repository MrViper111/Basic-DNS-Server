#include <_stdio.h>
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

int is_valid_ip(char *string) {
    struct in_addr addr;
    return inet_pton(AF_INET, string, &addr) == 1;
}

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
            printf("CLEARED EXISTING CACHE.\n");

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

        if (strncmp(command, "get ", 4) == 0 && is_valid_ip(buffer)) {
            if (get_value(CACHE_PATH, command + 4) != 0) {
                printf("DOMAIN ALREADY CACHED, USING EXISTING DATA.\n");
                continue;
            }

            char new_data[100];
            snprintf(new_data, sizeof(new_data), "%s:%s", command + 4, buffer);
            
            write_to(CACHE_PATH, new_data);
            printf("NEW RECORD ADDED TO CACHE.\n");
        }
    }
    
    close(sock);
    return 0;
}
