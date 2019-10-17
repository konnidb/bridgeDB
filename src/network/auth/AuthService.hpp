#pragma once
#include <string>
#include <iostream>
using namespace std;

class AuthService
{
private:
    /* data */
public:
    AuthService();
    static bool validate_credentials(string username, string password);
    static string generate_token(string, string);
    static bool validate_token(string);
    ~AuthService();
};
