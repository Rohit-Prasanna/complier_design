%{
#include <stdio.h>
#include <ctype.h>
#define YYSTYPE double

int yylex();
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
lines:
      lines expr '\n'   { printf("%g\n", $2); }
    | lines '\n'
    | /* empty */
    ;

expr:
      expr '+' expr     { $$ = $1 + $3; }
    | expr '-' expr     { $$ = $1 - $3; }
    | expr '*' expr     { $$ = $1 * $3; }
    | expr '/' expr     { $$ = $1 / $3; }
    | '(' expr ')'      { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | NUMBER
    ;
%%

int yylex() {
    int c;

    // Skip whitespace
    while ((c = getchar()) == ' ' || c == '\t');

    // End of file
    if (c == EOF)
        return 0;

    // Handle numbers
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }

    // Return single character tokens (+, -, *, /, (, ))
    return c;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

int main() {
    return yyparse();
}
