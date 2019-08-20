#include <iostream>
#include "parser.tab.c"
#include "lex.yy.c"
using namespace std;

int main() {
  YY_BUFFER_STATE buffer = yy_scan_string("MATCH");
  yyparse();
  yy_delete_buffer(buffer);
  return 0;
}