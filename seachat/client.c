#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


void close_socket(int sock) {
    int ret = close(sock);

    if (ret == -1) {
        perror("Error while closing socket");
    }
}


int setup_socket(const char ip_addr[], const uint16_t port) {
    int ret; // storage for return codes.

    // Request socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("Error during socket creation");
        return -1;
    }

    // Build address struct
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    ret = inet_pton(AF_INET, ip_addr, &addr.sin_addr);

    if (ret == 0) {
        fprintf(stderr, "Invalid destination address specified.\n");
        close_socket(sock);
        return -1;
    } else if (ret == -1) {
        fprintf(stderr, "Specified address family is not supported.\n");
        close_socket(sock);
        return -1;
    }

    // Connect
    ret = connect(sock, (const struct sockaddr *) &addr, sizeof(addr));

    if (ret == -1) {
        perror("Error while establishing connection");
        close_socket(sock);
        return -1;
    }

    return sock;
}


int main(void) {
    // Initialize socket
    int sock = setup_socket("127.0.0.1", 8080);

    if (sock == -1) {
        return EXIT_FAILURE;
    }

    // Send Data
    char msg[] = "Hello, World!\n";
    size_t len = strlen(msg);
    ssize_t bytes_sent = send(sock, msg, len, 0);

    printf(">>> %s", msg);

    // Close connection
    close_socket(sock);

    return 0;
}
