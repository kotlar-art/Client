//
// Created by lenovo on 1/4/2021.
//

#ifndef ASS3CLIENT_READER_H
#define ASS3CLIENT_READER_H
#include <connectionHandler.h>
#include <mutex>
#include <thread>
#include <condition_variable>
class Reader {
private:
    ConnectionHandler *connectionHandler;
    bool toTerminate;
    std::mutex& _mut;
    std::condition_variable& cv;
public:
    Reader(ConnectionHandler *handler, std::condition_variable& c, std::mutex& mut);
    bool read();
    bool write();
};


#endif
