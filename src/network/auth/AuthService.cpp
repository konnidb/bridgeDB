#include <iostream>
#include <set>
#include <string>
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

AuthData AuthService::get_credentials(string token) {
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
    
    return true;
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
    vector<pair<string, string>> stored_vector;
    ifstream userfile_i("au.th", ios::binary);
    if (user.is_root) {

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