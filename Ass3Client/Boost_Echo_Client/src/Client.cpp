//
// Created by spl211 on 02/01/2021.
//

#include <iostream>
#include <connectionHandler.h>
#include "Client.h"

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

    while (1) {
        std::string s;
        std::cin>>s;
        std::string command = "";
        int i = 0;
        while (s[i]!=' '){
            command = command + s[i];
            i++;
        }
        bool sent;
        std::string sub = "";
        if (command.compare("ADMINREG")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 1);
        }
        if (command.compare("STUDENTREG")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 2);
        }
        if (command.compare("LOGIN")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 3);
        }
        if (command.compare("LOGOUT")){
            sub = "";
            sent = connectionHandler.sendLine(sub, 4);
        }
        if (command.compare("COURSEREG")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 5);
        }
        if (command.compare("KDAMCHECK")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 6);
        }
        if (command.compare("COURSESTAT")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 7);
        }
        if (command.compare("STUDENTSTAT")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 8);
        }
        if (command.compare("ISREGISTERED")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 9);
        }
        if (command.compare("UNREGISTER")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 10);
        }
        if (command.compare("MYCOURSES")){
            sub = s.substr(i+1);
            sent = connectionHandler.sendLine(sub, 11);
        }
        if (!sent) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends the opcode in bytes to the string so it sends +2 bytes
        std::cout << "Sent " << sub.length()+2 << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout<<answer;
        if (answer == "ACK 4") break;
    }
    return 0;
}
