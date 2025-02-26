#ifndef USER_H
#define USER_H

#include <string>
#include "server.h"
#include "crypto.h"

class Server;

class User {
public:
    User(std::string name, std::string private_key, Server* server);
    std::string get_username() const;
    bool send_text_message(std::string text, std::string receiver);
    bool send_voice_message(std::string receiver);
private:
    std::string username;
    std::string private_key;
    Server* const server;
};

#endif //USER_H