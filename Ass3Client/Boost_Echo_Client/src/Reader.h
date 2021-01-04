//
// Created by lenovo on 1/4/2021.
//

#ifndef ASS3CLIENT_READER_H
#define ASS3CLIENT_READER_H
#include <connectionHandler.h>

class Reader {
private:
    ConnectionHandler connectionHandler;
public:
    Reader(const ConnectionHandler& handler);
    bool read();
};


#endif
