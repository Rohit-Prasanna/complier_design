%%
[a-z]+.vikram.com    { printf("Website\n"); }
.+           { printf("Not a website\n"); }
[ \t\n]+     ;
%%

int main() {
    yylex();
    return 0;
}
