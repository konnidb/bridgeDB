#pragma once
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

bool simpleMatch(char *query) {
    yy_scan_buffer(query);
    yylex();
}
