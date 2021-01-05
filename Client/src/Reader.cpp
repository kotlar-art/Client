//
// Created by lenovo on 1/4/2021.
//

#include "Reader.h"

Reader::Reader(ConnectionHandler *handler, std::condition_variable& c, std::mutex& mut): connectionHandler(handler), toTerminate(false), _mut(mut), cv(c){}

bool Reader::read() {
    while (1) {
        std::string answer;
        if (!connectionHandler->getFrameAscii(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout << answer;
        if (answer == "ACK 4") {
            toTerminate = true;
            cv.notify_all();
            break;
        }
    }
    return false;
}

bool Reader::write() {
    while (1) {

        std::string s;
        std::cin >> s;
        std::string command;
        int i = 0;
        while (s[i] != ' ') {
            command.push_back(s[i]);
            i++;
        }
        bool sent;
        std::string sub = "";
        if (command=="ADMINREG") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 1);
        }
        if (command=="STUDENTREG") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 2);
        }
        if (command=="LOGIN") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 3);
        }
        if (command=="LOGOUT") {
            sub = "";
            sent = connectionHandler->sendFrameAscii(sub, 4);
            std::unique_lock<mutex> lock(_mut);
            cv.wait(lock);
            if (toTerminate) return true;
        }
        if (command=="COURSEREG") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 5);
        }
        if (command=="KDAMCHECK") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 6);
        }
        if (command=="COURSESTAT") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 7);
        }
        if (command=="STUDENTSTAT") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 8);
        }
        if (command=="ISREGISTERED") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 9);
        }
        if (command=="UNREGISTER") {
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 10);
        }
        if (command=="MYCOURSES") {
            sub = "";
            sent = connectionHandler->sendFrameAscii(sub, 11);
        }
        if (!sent) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
    }
    return false;
}