#ifndef VALIDATION_FUNCTIONS_CLASS
#define VALIDATION_FUNCTIONS_CLASS

#include <istream>
#include <string.h>
#include "types_enum.hpp"

using namespace std;

class validation_functions
{
private:
public:
    validation_functions();
    template<typename T>
    static bool greater_than(void *arg, void *control, TYPE t)
    {
        return *static_cast<T *>(arg) > *static_cast<T *>(control);
    }
    template <typename T>
    static bool lower_than(void *arg, void *control, TYPE t)
    {

    }
    template <typename T>
    static bool equals(void *arg, void *control, TYPE t)
    {

    }

    template <typename T>
    static bool greater_eq(void *arg, void *control, TYPE t)
    {

    }

    template <typename T>
    static bool lower_eq(void *arg, void *control, TYPE t)
    {

    }

    ~validation_functions();
};

#endif