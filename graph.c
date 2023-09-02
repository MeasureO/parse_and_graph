#include <stdio.h>
#include <string.h>

#include "stack.h"
#define MAX 1000
#define symbols "+-*/ctskql()"

int to_polish(char *input, int len, char *output, Stack *top) {
    char *tmp = malloc(sizeof(char) * 2);
    char *tmp0 = malloc(sizeof(char));
    // int num = 0;
    // int num_flag = 0;
    for (int i = 0; i < len; i++) {
        if ((input[i] >= '0' && input[i] <= '9')) {
            // if (num_flag) {
            //     tmp0[0] = input[i];
            //     strcat(output, tmp0);
            // } else {
            if ((i <= len - 2) && (input[i + 1] < '0' || input[i + 1] > '9')) {
                tmp[0] = input[i];
                tmp[1] = ' ';
                strcat(output, tmp);
            } else {
                tmp0[0] = input[i];
                // tmp[1] = ' ';
                strcat(output, tmp0);
            }
            // }
            // num_flag = 1;
            // num = 10 * num + (int) input[i];
        }

        if (input[i] == 'x') {
            tmp[0] = input[i];
            tmp[1] = ' ';
            strcat(output, tmp);
            // num_flag = 0;
        }

        int nonbinoper_flag = 0;
        int binoper_flag = 0;
        // int symb_flag = 0;
        for (int j = 0; j < (int)strlen(symbols); j++) {
            if (input[i] == symbols[j] && input[i] != ')' && j >= 4 && j <= 10) nonbinoper_flag = 1;
        }
        if (nonbinoper_flag) {
            top = push(top, input[i]);
            // num_flag = 0;
        }

        if (input[i] == ')') {
            printf("4\n");

            while (1) {
                char c = pop(&top);
                if (c == '(') {
                    // top = push(top, '(');
                    break;
                } else {
                    tmp[0] = c;
                    tmp[1] = ' ';
                    strcat(output, tmp);
                }
            }
            printf("5\n");
            // num_flag = 0;
        }

        for (int j = 0; j < (int)strlen(symbols); j++) {
            if (input[i] == symbols[j] && input[i] != ')' && j <= 3) binoper_flag = 1;
        }
        printf("6\n");

        if (binoper_flag) {
            while (top->body != '\0') {
                printf("aas\n");
                print(top);
                printf("aaz\n");
                char c = pop(&top);
                if (c == 'c' || c == 't' || c == 's' || c == 'k' || c == 'q' || c == 'l') {
                    printf("a %c %c\n", input[i], c);
                    tmp[0] = c;
                    tmp[1] = ' ';
                    strcat(output, tmp);
                    printf("aa %c\n", c);

                } else if ((input[i] == '+' || input[i] == '-') &&
                           (c == '*' || c == '/' || c == '+' || c == '-')) {
                    printf("b %c\n", c);
                    tmp[0] = c;
                    tmp[1] = ' ';
                    strcat(output, tmp);
                } else if ((input[i] == '*' || input[i] == '/') && (c == '*' || c == '/')) {
                    printf("c %c\n", c);
                    tmp[0] = c;
                    tmp[1] = ' ';
                    strcat(output, tmp);
                } else {
                    printf("d %c\n", c);
                    top = push(top, c);
                    printf("sss\n");
                    break;
                }
            }
            printf("sss\n");

            top = push(top, input[i]);
        }
        printf("7\n");
    }

    while (top->next != NULL) {
        tmp[0] = ' ';
        tmp[1] = pop(&top);
        // printf("%c", tmp[1]);
        strcat(output, tmp);
        // if (top->next != NULL) top = top->next;
    }
    print(top);
    free(tmp);
    free(tmp0);
    return 0;
}

// int input_number() {

// }
char *str_replace(char *orig, char *rep, char *with) {
    char *result;   // the return string
    char *ins;      // the next insert point
    char *tmp;      // varies
    int len_rep;    // length of rep (the string to remove)
    int len_with;   // length of with (the string to replace rep with)
    int len_front;  // distance between rep and end of last rep
    int count;      // number of replacements

    // sanity checks and initialization
    if (!orig || !rep) return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0) return NULL;  // empty rep causes infinite loop during count
    if (!with) with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    // tmp = result;

    if (!result) return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;  // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

int main() {
    char *input = "123*cos(x+3)+sqrt(32*x+567)+777";
    char *output = malloc(sizeof(char));
    // fgets(input, MAX, stdin);
    char *str = str_replace(input, "cos", "c");
    // free(input);
    input = str_replace(str, "sin", "s");
    free(str);
    str = str_replace(input, "ctg", "k");
    free(input);
    input = str_replace(str, "tg", "t");
    free(str);
    str = str_replace(input, "sqrt", "q");
    free(input);
    input = str_replace(str, "ln", "l");
    free(str);
    printf("1\n");

    printf("%s\n", input);
    Stack *top = init('\0');
    printf("2\n");
    to_polish(input, strlen(input), output, top);
    printf("3\n");

    printf("\n");
    printf("%s", output);
    // for (int i = 0; i < (int)strlen(output);i++) printf("%c ", output[i]);
    free(input);
    // free(top);
    free(output);
    destroy(top);
    return 0;
}

// #include <stdio.h>
// #include <string.h>
// #include "stack.h"
// #define MAX 1000
// #define symbols "+-*/()ctskql~"

// int to_polish(char* input, int len, char* output, Stack* top) {
//     char *tmp = malloc(sizeof(char) * 2);
//     char *tmp0 = malloc(sizeof(char));
//     //int num = 0;
//     //int num_flag = 0;
//     for (int i = 0; i < len; i++) {
//         int nonbinoper_flag = 0;
//         int binoper_flag = 0;
//         //int unar_minus = 0;
//        // if (i == 0 && input[i] == '-') unar_minus = 1;
//         //int symb_flag = 0;
//         for(int j = 0; j <  (int) strlen(symbols);j++) {
//             if (input[i] == symbols[j] && input[i] != ')' && j >= 4) nonbinoper_flag = 1;
//         }
//         if (nonbinoper_flag) {
//             top = push(top, input[i]);
//             // num_flag = 0;
//         }

//         for(int j = 0; j <  (int) strlen(symbols);j++) {
//             if (input[i] == symbols[j] && input[i] != ')' && j <= 3) binoper_flag = 1;
//         }
//         if (binoper_flag) {
//             while(top->next != NULL) {
//                 char c = pop(&top);
//                 if (c == 'c' || c == 't' || c == 's' || c == 'k' || c == 'q' || c == 'l') {
//                     tmp[0] = c;
//                     tmp[1] = ' ';
//                     strcat(output, tmp);
//                 } else if ((input[i] == '+' || input[i] == '-') && (c == '*' || c == '/' || c == '+' || c
//                 == '-')) {
//                     tmp[0] = c;
//                     tmp[1] = ' ';
//                     strcat(output, tmp);
//                 } else if ((input[i] == '*' || input[i] == '/') && (c == '*' || c == '/')) {
//                     tmp[0] = c;
//                     tmp[1] = ' ';
//                     strcat(output, tmp);
//                 } else {
//                     top = push(top, c);
//                     break;
//                 }
//             }
//             top = push(top, input[i]);
//         }

//         if (input[i] == 'x') {
//             tmp[0] = input[i];
//             tmp[1] = ' ';
//             strcat(output, tmp);
//             // num_flag = 0;
//         }

//         if (input[i] == ')') {
//             while(1) {
//                 char c = pop(&top);
//                 if (c == '(') {
//                     //top = push(top, '(');
//                     break;
//                 } else {
//                     tmp[0] = c;
//                     tmp[1] = ' ';
//                     strcat(output, tmp);
//                 }
//             }
//             // num_flag = 0;
//         }

//         if ((input[i] >= '0' && input[i] <= '9')) {
//             // if (num_flag) {
//             //     tmp0[0] = input[i];
//             //     strcat(output, tmp0);
//             // } else {
//             if ((i <= len - 2) &&(input[i + 1] < '0' || input[i + 1] > '9')) {
//                 tmp[0] = input[i];
//                 tmp[1] = ' ';
//                 strcat(output, tmp);
//             } else {
//                 tmp0[0] = input[i];
//                 // tmp[1] = ' ';
//                 strcat(output, tmp0);
//             }
//             // }
//             // num_flag = 1;
//             //num = 10 * num + (int) input[i];
//         }

//     }

//     while(top->next != NULL) {
//         tmp[0] = ' ';
//         tmp[1] = pop(&top);
//         //printf("%c", tmp[1]);
//         strcat(output, tmp);
//         //if (top->next != NULL) top = top->next;
//     }
//     print(top);
//     free(tmp);
//     free(tmp0);
//     return 0;
// }

// // int input_number() {

// // }
// char *str_replace(char *orig, char *rep, char *with) {
//     char *result; // the return string
//     char *ins;    // the next insert point
//     char *tmp;    // varies
//     int len_rep;  // length of rep (the string to remove)
//     int len_with; // length of with (the string to replace rep with)
//     int len_front; // distance between rep and end of last rep
//     int count;    // number of replacements

//     // sanity checks and initialization
//     if (!orig || !rep)
//         return NULL;
//     len_rep = strlen(rep);
//     if (len_rep == 0)
//         return NULL; // empty rep causes infinite loop during count
//     if (!with)
//         with = "";
//     len_with = strlen(with);

//     // count the number of replacements needed
//     ins = orig;
//     for (count = 0; (tmp = strstr(ins, rep)); ++count) {
//         ins = tmp + len_rep;
//     }

//     tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

//     if (!result)
//         return NULL;

//     // first time through the loop, all the variable are set correctly
//     // from here on,
//     //    tmp points to the end of the result string
//     //    ins points to the next occurrence of rep in orig
//     //    orig points to the remainder of orig after "end of rep"
//     while (count--) {
//         ins = strstr(orig, rep);
//         len_front = ins - orig;
//         tmp = strncpy(tmp, orig, len_front) + len_front;
//         tmp = strcpy(tmp, with) + len_with;
//         orig += len_front + len_rep; // move to next "end of rep"
//     }
//     strcpy(tmp, orig);
//     return result;
// }

// int main() {
//     char* input = "123*cos(x+3)+sqrt(32*x+567)+777";
//     //char* input = "ln(x)";
//     char* output = malloc(sizeof(char));
//     // fgets(input, MAX, stdin);
//     char* str = str_replace(input, "cos", "c");
//     // free(input);
//     input = str_replace(str, "sin", "s");
//     free(str);
//     str = str_replace(input, "ctg", "k");
//     free(input);
//     input = str_replace(str, "tg", "t");
//     free(str);
//     str = str_replace(input, "sqrt", "q");
//     free(input);
//     input = str_replace(str, "ln", "l");
//     free(str);
//     printf("%s\n", input);
//     Stack* top = init('\0');
//     to_polish(input, strlen(input), output, top);
//     printf("\n");
//     printf("%s", output);
//     // for (int i = 0; i < (int)strlen(output);i++) printf("%c ", output[i]);
//     free(input);
//     // free(top);
//     free(output);
//     destroy(top);
//     return 0;
// }
