#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <IP_ADDRESS>\n", argv[0]);
        return 1;
    }
    
    uint32_t ip = inet_addr(argv[1]);
    
    if (ip == INADDR_NONE) {
        printf("Invalid IP address\n");
        return 1;
    }
    
    printf("%u\n", ip);
    return 0;
}
