#include <connectionHandler.h>
#include <iostream>
#include <sstream>
using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using namespace std;
ConnectionHandler::ConnectionHandler(string host, short port): host_(host), port_(port), io_service_(), socket_(io_service_){}
    
ConnectionHandler::~ConnectionHandler() {
    close();
}
 
bool ConnectionHandler::connect() {
    std::cout << "Starting connect to " 
        << host_ << ":" << port_ << std::endl;
    try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
 
bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
			tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);			
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {

			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
 
bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\n');
}

bool ConnectionHandler::sendLine(std::string& line) {
    return sendFrameAscii(line, '\n');
}

bool ConnectionHandler::sendLine(std::string& line, short opcode) {
    return sendFrameAscii(line, opcode);
}


bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char *ch;
    int position = 0;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
	    do{
            if (position==4){
                short AckOrError = bytesToShort(ch);
                short subject = bytesToShort(ch+2);
                if (AckOrError==13){
                    frame = "ERROR " + subject;
                    return true;
                }
                if (AckOrError==12) {
                    if (subject==6||subject==7||subject==8||subject==9||subject==11) frame = "ACK " + std::to_string(subject) + " ";
                    else {
                        frame = "ACK " + std::to_string(subject);
                        return true;
                    }
                }
                else throw new exception;
            }
		    if(!getBytes(ch+position, 1)) {
			    return false;
		    }
		    if (position>3) frame.append(1, ch[position]);
		    position++;
	    }
	    while (ch[position]!='\0');
    }
    catch (std::exception& e) {
	std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
	return false;
    }
    delete[] ch;
    return true;
}
 
bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
	bool result=sendBytes(frame.c_str(),frame.length());
	if(!result) return false;
	return sendBytes(&delimiter,1);
}

bool ConnectionHandler::sendFrameAscii(const std::string& frame, short opcode) {
    int newLength;
    char *cstr;
    if (opcode==5||opcode==6||opcode==7||opcode==9||opcode==10){
        newLength=4;
        cstr = new char[newLength];
        shortToBytes(opcode, cstr);
        stringstream number(frame);
        short x = 0;
        number >> x;
        shortToBytes(x, cstr+2);
    }
    if (opcode==1||opcode==2||opcode==3||opcode==8){
        newLength = frame.length()+3;
        cstr = new char[newLength];
        shortToBytes(opcode, cstr);
        strcpy(cstr + 2, frame.c_str());
        cstr[newLength-1] = '\0';
        for (unsigned int i = 0; i<newLength; i++){
            if (cstr[i] == ' ')
                cstr[i] = '\0';
        }
    }
    if (opcode==4||opcode==11){
        newLength = 2;
        cstr = new char[newLength];
        shortToBytes(opcode,cstr);
    }
    bool result = sendBytes(cstr,newLength);
    delete[] cstr;
    if(!result) return false;
    return true;
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}
void ConnectionHandler::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

short bytesToShort(char* bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
