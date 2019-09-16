#include "Test.h"

Test::Test(){
    this->dummyPassword = "123";
    this->dummyToken = "equisDe";
    this->dummyUser = "ivan";
}

string Test::getUser(){
    return this->dummyUser;
}
string Test::getPassword(){
    return this->dummyPassword;
}

string Test::getToken(){
    //Do some fancy stuff to create a fancy token
    return this->dummyToken;
}

bool Test::auth(string user, string password){
    if (user == getUser() && password == getPassword()){
        return true;
    }else{
        return false;
    }
}