cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(Client/include)

add_executable(Client
        Client/include/connectionHandler.h
        Client/src/connectionHandler.cpp
        Client/makefile
        Client/src/Client.cpp
        Client/include/Client.h
        Client/src/Reader.cpp
        Client/include/Reader.h)
