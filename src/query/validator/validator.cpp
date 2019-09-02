#include "validator.hpp"
#include <iostream>
#include <string.h>
#include "types_enum.hpp"

using namespace std;

validator::validator() {};

bool validator::validate_schema(void* node, Schema* schema)
{
    return false;
}

validator::~validator() {};
