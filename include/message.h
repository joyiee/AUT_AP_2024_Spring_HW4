#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include<iostream>
#include <vector>
class Message{
public:
    //Constructors
    Message(std::string type, std::string sender, std::string receiver);
    Message();

    //Getter functions
    std::string get_type() const;
    std::string get_sender() const;
    std::string get_receiver() const;
    std::string get_time() const;

    virtual void print(std::ostream &os) const; 

    friend std::ostream& operator<<(std::ostream &os, const Message &msg);

private:
    std::string type;
    std::string sender;
    std::string receiver;
    std::string time;
};

class TextMessage : public Message
{
private:
    std::string text;
public:
    TextMessage(std::string text, std::string sender, std::string receiver);
    void print(std::ostream &os) const override;
    std::string get_text() const;
};

class VoiceMessage : public Message
{
private:
    std::vector<unsigned char> voice;
public:
    VoiceMessage(std::string sender, std::string receiver);
    void print(std::ostream &os) const override;

    std::vector<unsigned char> get_voice() const;
};

#endif //MESSAGE_H