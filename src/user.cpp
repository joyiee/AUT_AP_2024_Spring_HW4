#include "user.h"

User::User(std::string name, std::string private_key, Server* server):\
username(name), private_key(private_key), server(server){};

std::string User::get_username()const
{
    return username;
}

bool User::send_text_message(std::string text, std::string receiver)
{
    TextMessage* msg =  new TextMessage(text, this->username, receiver);
    return this->server->create_message(msg, crypto::signMessage(private_key, "my data"));
}

bool User::send_voice_message(std::string receiver)
{
    VoiceMessage* msg =  new VoiceMessage(this->username, receiver);
    return this->server->create_message(msg, crypto::signMessage(private_key, "my data"));
} 
