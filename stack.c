#include "stack.h"

Stack* init(const char in) {
    Stack* root = malloc(sizeof(Stack));
    if (root != NULL) {
        root->body = in;
        root->next = NULL;
    }
    return root;
}
Stack* push(Stack* elem, const char in) {
    Stack* root = malloc(sizeof(Stack));
    if (root != NULL) {
        root->next = elem;
        root->body = in;
        return root;
    }
    return elem;
}
int pop(Stack** root) {
    if ((*root)->next == NULL) {
        int out = (*root)->body;
        free(*root);
        *root = NULL;
        return out;
    }
    Stack* for_del = *root;
    int out = (*root)->body;
    *root = (*root)->next;
    free(for_del);
    return out;
}
void destroy(Stack* root) {
    if (root != NULL) {
        Stack* current_node = root;
        Stack* for_del = current_node;
        if (root->next == NULL) {
            free(root);
        } else {
            // LETS GO TO THE TODEL
            while (current_node != NULL) {
                current_node = for_del->next;
                free(for_del);
                for_del = current_node;
            }
        }
    }
}

void print(Stack* root) {
    Stack* cur = root;
    printf("|%c| %lX\n", cur->body, (long int)root);
    while ((cur = cur->next) != NULL) {
        printf("|%c| %lX\n", cur->body, (long int)cur);
    }
}

// void print(Stack* root) {
//     Stack* cur = root;
//     printf("%c | %lX |\n", cur->body, (long int)cur);
//     while ((cur = cur->next) != NULL) {
//         printf("%c | %lX |\n", cur->body, (long int)cur);
//     }
// }
