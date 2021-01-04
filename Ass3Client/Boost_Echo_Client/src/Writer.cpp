//
// Created by lenovo on 1/4/2021.
//

#include "Writer.h"

Writer::Writer(const ConnectionHandler& handler): connectionHandler(handler) {}

bool Writer::write() {
    while (1) {
        std::string s;
        std::cin >> s;
        std::string command = "";
        int i = 0;
        while (s[i] != ' ') {
            command = command + s[i];
            i++;
        }
        bool sent;
        std::string sub = "";
        if (command.compare("ADMINREG")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 1);
        }
        if (command.compare("STUDENTREG")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 2);
        }
        if (command.compare("LOGIN")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 3);
        }
        if (command.compare("LOGOUT")) {
            sub = "";
            sent = connectionHandler.sendLine(sub, 4);
        }
        if (command.compare("COURSEREG")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 5);
        }
        if (command.compare("KDAMCHECK")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 6);
        }
        if (command.compare("COURSESTAT")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 7);
        }
        if (command.compare("STUDENTSTAT")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 8);
        }
        if (command.compare("ISREGISTERED")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 9);
        }
        if (command.compare("UNREGISTER")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 10);
        }
        if (command.compare("MYCOURSES")) {
            sub = s.substr(i + 1);
            sent = connectionHandler.sendLine(sub, 11);
        }
        if (!sent) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        return false;
    }
}