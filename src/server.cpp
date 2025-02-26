#include "server.h"
#include <algorithm>

Server::Server(){};

std::vector<User> Server::get_users() const
{
    return users;
}

std::map<std::string, std::string> Server::get_public_keys() const
{
    return public_keys;
}


std::vector<Message*> Server::get_messages() const
{
    return messages;
}

std::vector<Message*> Server::get_all_messages_from(std::string username) const
{
    std::vector<Message*> res;
    if(public_keys.find(username)!= public_keys.end())
    {
        for(auto message:messages)
        {
            if(message->get_sender()== username)
                res.push_back(message);
        }
    }
    return res;
}

std::vector<Message*> Server::get_all_messages_to(std::string username) const
{
    std::vector<Message*> res;
    if(public_keys.find(username)!= public_keys.end())
    {
        for(auto message:messages)
        {
            if(message->get_receiver()== username)
                res.push_back(message);
        }
    }
    return res;
}

std::vector<Message*> Server::get_chat(std::string user1, std::string user2) const
{
    std::vector<Message*> res;
    if(public_keys.find(user1)!= public_keys.end() && public_keys.find(user2)!=public_keys.end())
    {
        for(auto message:messages)
        {
            if((message->get_sender()== user1 && message->get_receiver() == user2) || (message->get_sender()== user2 && message->get_receiver() == user1))
                res.push_back(message);
        }
    }
    return res;
}

void Server::sort_msgs(std::vector<Message*> &msgs)
{
    std::sort(msgs.begin(), msgs.end(), [](Message* a, Message* b) {
        return a->get_time() < b->get_time();
    });
}

User Server::create_user(std::string username)
{
    if(public_keys.find(username)!=public_keys.end())
        throw std::logic_error("The user already exists");
    // generate private and public key pair
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    //generate user and add to lists
    User user = User(username, private_key, this);
    users.push_back(user);
    public_keys[username] = public_key;
    return user;
}

bool Server::create_message(Message* msg, std::string signature)
{
    //verify the signature
    std::string sender = msg->get_sender();
    std::string receiver = msg->get_receiver();
    if(public_keys.find(sender)!=public_keys.end() && public_keys.find(receiver)!=public_keys.end())
    {
        std::string pub_key = public_keys[sender];
        if(crypto::verifySignature(pub_key, "my data", signature))
        {
            messages.push_back(msg);
            return true;
        }
        else return false;
    }
    else return false;
}

