#include <iostream>
#include "parser.tab.c"
#include "lex.yy.c"
using namespace std;

int main() {
  YY_BUFFER_STATE buffer = yy_scan_string("MATCH");
  int result = yyparse();
  cout<<result<<endl;
  yy_delete_buffer(buffer);
  return result;
}