#include <iostream>
#include "AuthService.cpp"
#include <string>

using namespace std;

int main() {
    string token = AuthService::generate_token("my name is yiyo", "databaseshida");
    cout << token << endl;
    AuthService::validate_token("asdnaskjdnakjdn");
}