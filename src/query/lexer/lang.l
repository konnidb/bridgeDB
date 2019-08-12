string	\"[^\n"]+\"
%{
#include "constants.h"
%}
%%
"("     return OPEN_PARENTHESIS;
")"     return CLOSE_PARENTHESIS;
"{"     return OPEN_C_BRACE;
"}"     return CLOSE_C_BRACE;
"["     return OPEN_BRACE;
"]"     return CLOSE_BRACE;
"-"     return HYPHEN;
"."     return DOT;
{string}	return STRING;
\n          return EOL;

%%

int yywrap(void) {
    return 1;
}