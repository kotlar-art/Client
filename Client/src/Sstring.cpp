
#include "../include/Sstring.h"


string Sstring::getContent() {
    return content_;
}

void Sstring::setContent(string content) {
    content_ = content;
}

Sstring::Sstring(string content): content_(content) {

}

void Sstring::append(char c) {
    content_.push_back(c);
}
