CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -pthread


all:bin/BGRSclient
bin/BGRSclient:bin/Client.o bin/connectionHandler.o bin/Reader.o bin/Sstring.o
	@echo 'Building target: Client'
	@echo 'Invoking: C++ Linker'
	g++ -Wall -Weffc++ -o bin/BGRSclient bin/Client.o bin/connectionHandler.o bin/Reader.o bin/Sstring.o $(LDFLAGS)
	@echo 'Finished building target: Client'
	@echo ' '


bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/Reader.o: src/Reader.cpp
	g++ $(CFLAGS) -o bin/Reader.o src/Reader.cpp

bin/Sstring.o: src/Sstring.cpp
	g++ $(CFLAGS) -o bin/Sstring.o src/Sstring.cpp

clean:
	rm -f bin/*
