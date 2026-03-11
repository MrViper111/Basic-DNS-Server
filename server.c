#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "util.h"

#define PORT 8080
#define BUFFER_SIZE 1024
#define CLIENT_BACKLOG 5
#define DATA_PATH "data.txt"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr))) {
        perror("BIND FAILED.");
        close(sock);
        return 1;
    }

    if (listen(sock, CLIENT_BACKLOG)) {
        perror("FAILED TO LISTEN.");
        close(sock);
        return 1;
    }

    printf("Server listening for connections on %d...\n", PORT);

    int clients_connected = 0;
    char buffer[BUFFER_SIZE];

    while (1) {
        int client = accept(sock, NULL, NULL);
        clients_connected++;
        printf("CLIENT HAS CONNECTED (%d)\n", clients_connected);

        while (1) {
             memset(buffer, 0, BUFFER_SIZE);
            int bytes = read(client, buffer, BUFFER_SIZE);

            if (bytes <= 0) {
                clients_connected--;
                printf("CLIENT DISCONNECTED (%d)\n", clients_connected);
                break;
            }

            printf("RECIEVED: %s\n", buffer);

            if (strncmp(buffer, "get ", 4) == 0) {
                char *key = buffer + 4;
                uint32_t ip = get_value(DATA_PATH, key);

                if (ip == 0) {
                    char *response = "Domain not found.";
                    send(client, response, strlen(response), 0);
                    continue;
                }
                printf("FOUND DNS RECORD FOR: %s\n", key);
    
                struct in_addr addr;
                addr.s_addr = ip;
                char *ip_str = inet_ntoa(addr);
    
                send(client, ip_str, strlen(ip_str), 0);

            } else if (strncmp(buffer, "put ", 4) == 0) {
                char *line = buffer + 4;
                write_to(DATA_PATH, line);
                printf("ADDED %s TO DNS RECORDS.\n", line);

                char *response = "ADDED TO DNS RECORDS.";
                send(client, response, strlen(response), 0);
            }
        }
  
    }
           
    close(sock);
    return 0;
}
