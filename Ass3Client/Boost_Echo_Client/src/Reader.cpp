//
// Created by lenovo on 1/4/2021.
//

#include "Reader.h"

Reader::Reader(const ConnectionHandler &handler): connectionHandler(handler) {}

bool Reader::read() {
    while (1) {
        std::string answer;
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout << answer;
        if (answer == "ACK 4") break;
    }
    return false;
}
