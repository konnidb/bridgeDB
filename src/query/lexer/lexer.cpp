#include <iostream>
#include "lex.yy.c"

int main(int argc, char const *argv[])
{
    std::cout<<"asd";
    yyin = stdin;
    int a = yylex();
    std::cout<<a<<std::endl;
    return 0;
}
