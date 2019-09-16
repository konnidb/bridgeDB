#pragma once
#include<iostream>
#include<string>
using namespace std;

class Test {
    public:
        Test();
        bool auth(string, string);
        string getUser();
        string getPassword();
        string getToken();
    private:
        string dummyUser;
        string dummyPassword;
        string dummyToken;
};