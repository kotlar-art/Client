//
// Created by spl211 on 02/01/2021.
//

#include <iostream>
#include <connectionHandler.h>
#include <thread>
#include "Reader.h"
#include <mutex>
#include <thread>

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    std::mutex mut;
    std::condition_variable c;
    Reader reader(&connectionHandler, c, mut);
    std::thread writer(&Reader::write,&reader);
    reader.read();
    return 0;
}
