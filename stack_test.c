#include "stack.h"

int list_len(Stack* root);
void cmp_int(const long int have, const long int ex);

int main() {
    Stack* top = init(1);
    top = push(top, 2);
    top = push(top, 3);
    top = push(top, 4);
    top = push(top, 5);
    top = push(top, 6);
    print(top);

    printf("===== test_push =====\n");
    cmp_int(list_len(top), 6);

    printf("==== test_pop ====\n");
    printf("returned and pop %d\n", pop(&top));
    print(top);
    cmp_int(list_len(top), 5);

    printf("==== test_pop2 ====\n");
    printf("returned and pop %d\n", pop(&top));
    print(top);
    cmp_int(list_len(top), 4);

    destroy(top);
    return 0;
}

int list_len(Stack* root) {
    if (root == NULL) return 0;
    Stack* cur = root;
    int count = 1;
    while ((cur = cur->next) != NULL) {
        ++count;
    }
    return count;
}

void cmp_int(const long int have, const long int ex) {
    if (have == ex) {
        printf("Wait: %ld; Have: %ld : TEST SUCCESS\n", ex, have);
    } else {
        printf("Wait: %ld; Have: %ld : TEST FAIL\n", ex, have);
    }
}