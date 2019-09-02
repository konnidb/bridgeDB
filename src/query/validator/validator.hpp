#ifndef VALIDATOR_CLASS
#define VALIDATOR_CLASS

#include <istream>
#include <string.h>

using namespace std;

class validator
{
private:
    /* data */
public:
    validator();
    bool validate_schema(void*, class Shema*);
    ~validator();
};


#endif
