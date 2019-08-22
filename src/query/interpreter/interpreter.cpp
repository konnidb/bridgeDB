#include <iostream>
#include "lex.yy.c"
#include "parser.tab.c"
using namespace std;
int main() {
  YY_BUFFER_STATE buffer = yy_scan_string("MATCH (n:Person) RETURN n.property");
  int result = yyparse();
  cout<<result<<endl;
  yy_delete_buffer(buffer);
  return result;
}