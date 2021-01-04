//
// Created by spl211 on 02/01/2021.
//

#include <iostream>
#include <connectionHandler.h>
#include <Writer.h>
#include <thread>
#include "Client.h"
#include "Reader.h"

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
    Writer writer(connectionHandler);
    Reader reader(connectionHandler);
    std::thread w(&Writer::write,&writer);
    reader.read();
    w.join();
    return 0;
}
