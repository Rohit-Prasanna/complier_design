#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0, j = 0;
char expr[100], left[10], right[10];
char temp = 'Z'; // Temporary variable names start from Z

struct op_pos {
    int pos;
    char op;
} ops[20];

void find_operators();
void generate_code();
void get_left(int pos);
void get_right(int pos);
void reverse_string(char *s); // replacement for strrev

int main() {
    printf("\n\tINTERMEDIATE CODE GENERATION\n");
    printf("--------------------------------------\n");
    printf("Enter the expression: ");
    scanf("%s", expr);

    printf("\nIntermediate code:\n");
    find_operators();
    generate_code();

    return 0;
}

void find_operators() {
    int len = strlen(expr);
    for (i = 0; i < len; i++)
        if (expr[i] == '=')
            ops[j].pos = i, ops[j++].op = '=';

    for (i = 0; i < len; i++)
        if (expr[i] == '/' || expr[i] == '*')
            ops[j].pos = i, ops[j++].op = expr[i];

    for (i = 0; i < len; i++)
        if (expr[i] == '+' || expr[i] == '-')
            ops[j].pos = i, ops[j++].op = expr[i];
}

void generate_code() {
    for (i = 0; ops[i].op != '\0'; i++) {
        get_left(ops[i].pos);
        get_right(ops[i].pos);

        printf("%c := %s %c %s\n", temp, left, ops[i].op, right);
        expr[ops[i].pos] = temp;  // Replace operator with temp variable
        temp--;                   // Next temporary variable
    }

    printf("%s := %c\n", expr, ++temp); // Final assignment
}

void get_left(int pos) {
    int k = pos - 1;
    int p = 0;
    while (k >= 0 && expr[k] != '+' && expr[k] != '-' && expr[k] != '*' &&
           expr[k] != '/' && expr[k] != '=' && expr[k] != '\0') {
        left[p++] = expr[k];
        expr[k] = '$';
        break;
    }
    left[p] = '\0';
    reverse_string(left); // fixed version of strrev
}

void get_right(int pos) {
    int k = pos + 1;
    int p = 0;
    while (expr[k] != '\0' && expr[k] != '+' && expr[k] != '-' &&
           expr[k] != '*' && expr[k] != '/' && expr[k] != '=' ) {
        right[p++] = expr[k];
        expr[k] = '$';
        break;
    }
    right[p] = '\0';
}

void reverse_string(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}
