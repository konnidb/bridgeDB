#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include "AuthService.hpp"
#include "src/jwt-cpp/include/jwt-cpp/jwt.h"
#include <fstream>
#include <ios>

using namespace std;

const string _db_str = "database";
const string _username_str = "username";

AuthService::AuthService()
{
}

AuthService::~AuthService()
{
}

string AuthService::generate_token(AuthCredentials credentials)
{
    string username = credentials.username;
    string password = credentials.password;
    string database = credentials.database;
    string graph = credentials.graph;
    auto c_username = username.c_str();
    auto c_database = database.c_str();
    auto token = jwt::create()
                     .set_issuer("auth0")
                     .set_type("JWS")
                     .set_payload_claim(_db_str, jwt::claim(string(c_database)))
                     .set_payload_claim(_username_str, jwt::claim(username))
                     .set_payload_claim("database", jwt::claim(database))
                     .set_payload_claim("graph", jwt::claim(graph))
                     .sign(jwt::algorithm::hs256{"supersecret"});
    return token;
}

AuthData AuthService::get_auth_data(string token) {
    AuthData data;
    auto decoded = jwt::decode(token);
    auto& username = decoded.get_payload_claim(_username_str);
    auto& database = decoded.get_payload_claim(_db_str);
    auto& graph = decoded.get_payload_claim("graph");
    cout << database.as_string().c_str();
    data.database_name = database.as_string();
    data.graph_name = graph.as_string();
    data.username = username.as_string();
    return data;

};

bool AuthService::validate_credentials(AuthCredentials credentials)
{
    bool flag = false;
    ifstream authFile;
    vector<string> tokens;
    authFile.open("au.th", ios::in);
    authFile.read((char*)&tokens, sizeof(tokens));
    for(string token: tokens) {
        auto decoded = jwt::decode(token);
        string username = decoded.get_payload_claim("username").as_string();
        if (strcmp(username.c_str(), credentials.username.c_str())) {
            string database = decoded.get_payload_claim("database").as_string();
            string graph = decoded.get_payload_claim("graph").as_string();
            if (strcmp(database.c_str(), credentials.database.c_str()) && strcmp(graph.c_str(), credentials.graph.c_str())) {
                flag = strcmp(
                    decoded.get_payload_claim("password").as_string().c_str(),
                    credentials.password.c_str()
                );
            }
        }
    }
    authFile.close();
    if (!authFile.good()) {
        throw "Failure opening file in Validate Credentials";
    }
    return flag;
}

bool AuthService::create_user(AuthCredentials credentials, AuthData user) {
    vector<AuthCredentials> credentialsVector;
    auto token = jwt::create()
                    .set_issuer("auth0")
                    .set_type("JWS")
                    .set_payload_claim("username", jwt::claim(credentials.username))
                    .set_payload_claim("password", jwt::claim(credentials.password))
                    .set_payload_claim("database", jwt::claim(credentials.database))
                    .set_payload_claim("graph", jwt::claim(credentials.graph))
                    .sign(jwt::algorithm::hs256{"supersecret"});
    // ifstream userfile_i("au.th", ios::binary);
    if (user.is_root) {
        vector<string> tokens;
        ifstream authFile;
        authFile.open("au.th", ios::in);
        authFile.read((char*)&tokens, sizeof(tokens));
        tokens.push_back(token);
        authFile.close();
        if (!authFile.good()) {
            throw "Failure reading auth file.";
        }
        ofstream writeFile;
        writeFile.open("au.th", ios::app);
        writeFile.write((char*)&tokens, sizeof(tokens));
        writeFile.close();
        if (!writeFile.good()) {
            throw "Failure creating user.";
        }
    }
};

AuthCredentials AuthService::get_stored_user(string username, string password) {
    
};

bool AuthService::validate_token(string token)
{
    auto decoded = jwt::decode(token);
    auto verify = jwt::verify()
                      .allow_algorithm(jwt::algorithm::hs256{"supersecret"})
                      .with_issuer("auth0");
    verify.verify(decoded);
    return true;
}

void AuthService::configurate_auth_file() {
    string fileName = "au.th";
    fstream authFile;
    authFile.open(fileName, fstream::in | fstream::out | fstream::app);
    if (!authFile) {
        cout << "CRAETING AUTH FILE..." << endl;
        authFile.open(fileName, fstream::in | fstream::out | fstream::trunc);
        vector<pair<string, string>> simplevector;
        pair<string, string> root("root", "supersecretpassword");
        simplevector.push_back(root);
        int size = simplevector.size();
        authFile.write((const char*)&simplevector, sizeof(root));
        authFile.close();
        cout << "AUTH FILE CREATED!" << endl;
    } else return;
}