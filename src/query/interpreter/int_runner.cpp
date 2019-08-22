#include <iostream>
#include "parser.tab.c"
#include "Interpreter.hpp"
// #include "parser.tab.c"
using namespace std;
// int parse_query(Interpreter *);
int main()
{
	Interpreter intr("MATCH (n:Person) RETURN n.property");
	cout<<"Hello world";
	parse_query(&intr);
	// YY_BUFFER_STATE buffer = yy_scan_string("MATCH (n:Person) RETURN n.property");
	// int result = yyparse();
	// cout << result << endl;
	// yy_delete_buffer(buffer);

	return intr.get_parse_result();
}

