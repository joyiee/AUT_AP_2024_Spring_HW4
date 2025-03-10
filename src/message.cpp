#include "message.h"
#include <ctime>
#include <random>

Message::Message(std::string type, std::string sender, std::string receiver) : type(type), sender(sender), receiver(receiver)
{
    auto now = std::time(nullptr);
    time = std::ctime(&now);
    time.pop_back();
}

Message::Message():type(""), sender(""), receiver(""){
    auto now = std::time(nullptr);
    time = std::ctime(&now);
    time.pop_back();
}

std::string Message::get_type() const
{
    return type;
}

std::string Message::get_sender() const
{
    return sender;
}

std::string Message::get_receiver() const
{
    return receiver;
}

std::string Message::get_time() const
{
    return time;
}

void Message::print(std::ostream &os) const
{
    os << "*************************\n" \
    << sender << " -> " << receiver << "\n" \
    << "message type: " << type << "\n" \
    << "message time: " << time << \
    "\n*************************" << std::endl;
}

std::ostream& operator<<(std::ostream &os, const Message &msg)
{
    msg.print(os);
    return os;
}

TextMessage::TextMessage(std::string text, std::string sender, std::string receiver):Message("text", sender, receiver), text(text) {};
void TextMessage::print(std::ostream &os) const
{
    os << "*************************\n" \
    << get_sender() << " -> " << get_receiver() << "\n" \
    << "message type: " << get_type() << "\n" \
    << "message time: " << get_time()  \
    << "text: " << text << \
    "\n*************************" << std::endl;
}

std::string TextMessage::get_text() const{
    return text;
}

VoiceMessage::VoiceMessage(std::string sender, std::string receiver):Message("voice", sender, receiver)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 255);

    for (int i = 0; i < 5; ++i) {
        voice.push_back(static_cast<unsigned char>(dist(gen)));
    }
}

void VoiceMessage::print(std::ostream &os) const
{
    os << "*************************\n" \
    << get_sender() << " -> " << get_receiver() << "\n" \
    << "message type: " << get_type() << "\n" \
    << "message time: " << get_time() \
    << "voice:";
    for(auto word : voice)
    {
        os << " " << static_cast<int>(word);
    }
    os << "\n*************************" << std::endl;
}

std::vector<unsigned char> VoiceMessage::get_voice() const{
    return voice;
}