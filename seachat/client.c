#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


struct config {
    char *peer_address;
    uint16_t peer_port;
    char *username;
};


void validate_username(const char *username) {
    const size_t len = strlen(username);

    if (len > 50) {
        fprintf(stderr, "Username cannot be larger than 50 characters.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len; i++) {
        const char current = username[i];

        if (!(
            (current >= 'a' && current <= 'z') ||
            (current >= 'A' && current <= 'Z') ||
            current == '_' || current == '.'
        )) {
            fprintf(
                stderr,
                "Username can only contain (a-z, A-Z, '_', '.').\n"
            );
            exit(EXIT_FAILURE);
        }
    }
}

uint16_t parse_port(const char *port_str) {
    char *end; // this is the last valid character consumed by `strtol()` in `port_str`.

    errno = 0;
    const long port = strtol(port_str, &end, 10);

    // over/underflow or invalid digits for a base.
    if (errno == ERANGE || errno == EINVAL) {
        perror("Invalid port");
        exit(EXIT_FAILURE);
    }

    // no valid characters found
    if (port_str == end) {
        fprintf(stderr, "Port is empty or contains no valid characters.\n");
        exit(EXIT_FAILURE);
    }

    // trailing non-numeric characters
    if (*end != '\0') {
        fprintf(stderr, "Port contains invalid characters.\n");
        exit(EXIT_FAILURE);
    }

    if (port < 0 || port > 65535) {
        fprintf(stderr, "Port should be within [0,65535].\n");
        exit(EXIT_FAILURE);
    }

    return (uint16_t) port;
}


void parse_cli_args(const int argc, char *argv[], struct config *cfg) {
    for (int i = 1; i < argc; i++) {
        // -h, --help
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf(
                "seachat-client - Client for a simple chat application.\n"
                "\n"
                "Usage:\n"
                "  seachat-client [OPTIONS]\n"
                "\n"
                "Options:\n"
                "  -h, --help     Show this help message and exit\n"
                "  -n, --name     Your name, can contain (a-z, A-Z, '_', '.'). Not more than 50 characters long.\n"
                "  -s, --host     IP address of the host you want to communicate with, which can also be a group.\n"
                "  -p, --port     Port on which the host you want to communicate with listens on. (Default: 54321)\n"
            );
            exit(EXIT_SUCCESS);
        }
        // -n, --name
        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--name") == 0) {
            validate_username(argv[i + 1]);
            cfg->username = argv[i + 1];
            i++;
        }
        // -h, --host
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--host") == 0) {
            cfg->peer_address = argv[i + 1];
            i++;
        }
        // -p, --port
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            cfg->peer_port = parse_port(argv[i + 1]);
            i++;
        }
    }
}


void close_socket(int sock) {
    int ret = close(sock);

    if (ret == -1) {
        perror("Error while closing socket");
    }
}


int setup_socket(const char ip_addr[], const uint16_t port) {
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
    int ret = inet_pton(AF_INET, ip_addr, &addr.sin_addr);

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


int main(const int argc, char *argv[]) {
    struct config cfg = {
        .peer_address = "127.0.0.1",
        .peer_port = 54321,
        .username = "anonymous"
    };

    parse_cli_args(argc, argv, &cfg);

    // Initialize socket
    const int sock = setup_socket(cfg.peer_address, cfg.peer_port);

    if (sock == -1) {
        return EXIT_FAILURE;
    }

    printf("Welcome to seachat, %s.\n", cfg.username);

    // Send Data
    char msg[] = "Hello, World!\n";
    size_t len = strlen(msg);
    ssize_t bytes_sent = send(sock, msg, len, 0);

    printf(">>> %s", msg);

    // Close connection
    close_socket(sock);

    return 0;
}
