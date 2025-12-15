#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PyListNode {
    char *value;
    struct PyListNode *next;
};

struct PyList {
    struct PyListNode *head;
    struct PyListNode *tail;
    int length;
};

struct PyList *list_init() {
    struct PyList *list = malloc(sizeof(struct PyList));

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

int list_append(struct PyList *list, const char *value) {
    /*
     * On Success, returns the new length of the list after appending.
     * It returns -1 on error, with errno set to indicate the error.
     */

    struct PyListNode *node = malloc(sizeof(struct PyListNode));
    if (node == NULL)
        return -1;

    node->value = strdup(value);
    if (node->value == NULL) {
        free(node);
        return -1;
    }
    node->next = NULL;

    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;

    return list->length;
}

void list_del(struct PyList *list) {
    struct PyListNode *node = list->head;
    while (node != NULL) {
        free(node->value);
        struct PyListNode *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(list);
}

void list_print(const struct PyList *list) {
    if (list->length == 0) {
        printf("[]\n");
        return;
    }

    const struct PyListNode *node = list->head;

    printf("[");
    while (node != NULL) {
        printf("\"%s\"", node->value);
        node = node->next;
        if (node != NULL)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    struct PyList *list = list_init();
    if (list == NULL) {
        perror("Error while allocating list memory");
        return EXIT_FAILURE;
    }

    list_append(list, "a");
    list_append(list, "b");

    list_print(list);

    list_del(list);
    return 0;
}
