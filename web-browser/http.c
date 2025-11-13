#include <sys/socket.h>

typedef struct {
    char *value;
    struct linked_list *next;
} linked_list;

typedef struct {
    char *scheme;
    char *hostname;
    linked_list *path;
    linked_list *query;
    char *fragment;
} uri;


int parse_url(char url[]) {
}

int main() {
    return 0;
}
