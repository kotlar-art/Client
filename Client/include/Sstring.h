//
// Created by spl211 on 05/01/2021.
//

#ifndef CLIENT_SSTRING_H
#define CLIENT_SSTRING_H
using namespace std;
#include <iostream>


class Sstring {
private:
    string content_;
public:
    Sstring(string content);
    void setContent(string content);
    string getContent();
    void append(char c);
};


#endif //CLIENT_SSTRING_H
