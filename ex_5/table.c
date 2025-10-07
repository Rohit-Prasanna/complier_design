#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char expr[50];
    void *address[20];
    char symbol[20];
    int i = 0, x = 0;

    printf("Enter the expression ending with $: ");
    while ((expr[i] = getchar()) != '$') {
        i++;
    }
    expr[i] = '\0';

    printf("\nGiven Expression: %s\n", expr);
    printf("\nSymbol Table\n");
    printf("Symbol\tAddress\t\tType\n");

    for (i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        if (isalpha(c)) {  // Identifier (a, b, x, y, etc.)
            address[x] = malloc(sizeof(char));
            symbol[x] = c;
            printf("%c\t%p\tIdentifier\n", c, address[x]);
            x++;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            address[x] = malloc(sizeof(char));
            symbol[x] = c;
            printf("%c\t%p\tOperator\n", c, address[x]);
            x++;
        }
    }

    // Free allocated memory
    for (i = 0; i < x; i++)
        free(address[i]);

    return 0;
}
