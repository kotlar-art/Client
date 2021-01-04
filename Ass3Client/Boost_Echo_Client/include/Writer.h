

#ifndef ASS3CLIENT_WRITER_H
#define ASS3CLIENT_WRITER_H
#include <connectionHandler.h>

class Writer {
private:
    ConnectionHandler connectionHandler;
public:
    Writer(const ConnectionHandler& handler);
    bool write();
};


#endif //ASS3CLIENT_WRITER_H
