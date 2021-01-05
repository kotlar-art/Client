//
// Created by lenovo on 1/4/2021.
//


#include "Reader.h"

Reader::Reader(ConnectionHandler *handler, std::condition_variable& c, std::mutex& mut): connectionHandler(handler), toTerminate(false), _mut(mut), cv(c){}

bool Reader::read() {
    while (true) {
        string answer;
        if (!connectionHandler->getFrameAscii(answer)) {
            std::cout << "Disconnected. Exiting... read \n" << std::endl;
            break;
        }
        std::cout << "funckinggggggggggg " + answer<<endl;
        if (answer == "ACK 4") {
            toTerminate = true;
            cv.notify_all();
            break;
        }
    }
    return false;
}

bool Reader::write() {
    while (true) {
        const short bufsize = 1024;
        char buf[bufsize];
        cout<<"please type a command"<<endl;
        std::cin.getline(buf, bufsize);
        std::string s(buf);
        cout<< "typed string " + s<<endl;
        std::string command;
        int i = 0;
        while (s[i] != ' ') {
            command.push_back(s[i]);
            i++;
        }
        cout<<"command is " << command <<endl;
        bool sent;
        std::string sub = "";
        if (command=="ADMINREG") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i+1);
            sent = connectionHandler->sendFrameAscii(sub, 1);
        }
        if (command=="STUDENTREG") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 2);
        }
        if (command=="LOGIN") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 3);
        }
        if (command=="LOGOUT") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = "";
            sent = connectionHandler->sendFrameAscii(sub, 4);
            std::unique_lock<mutex> lock(_mut);
            cv.wait(lock);
            if (toTerminate) return true;
        }
        if (command=="COURSEREG") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 5);
        }
        if (command=="KDAMCHECK") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 6);
        }
        if (command=="COURSESTAT") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 7);
        }
        if (command=="STUDENTSTAT") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 8);
        }
        if (command=="ISREGISTERED") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 9);
        }
        if (command=="UNREGISTER") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = s.substr(i + 1);
            sent = connectionHandler->sendFrameAscii(sub, 10);
        }
        if (command=="MYCOURSES") {
            cout<<"recognized that you wanted " + command<<endl;
            sub = "";
            sent = connectionHandler->sendFrameAscii(sub, 11);
        }
        if (!sent) {
            std::cout << "Disconnected. Exiting... write \n" << std::endl;
            break;
        }
    }
    return false;
}
