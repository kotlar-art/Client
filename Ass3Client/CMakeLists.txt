cmake_minimum_required(VERSION 3.17)
project(Ass3Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(Boost_Echo_Client/include)

add_executable(Ass3Client
        Boost_Echo_Client/include/connectionHandler.h
        Boost_Echo_Client/src/connectionHandler.cpp
        Boost_Echo_Client/src/echoClient.cpp
        Boost_Echo_Client/makefile Boost_Echo_Client/src/Client.cpp Boost_Echo_Client/src/Client.h Boost_Echo_Client/src/EncoderDecoder.cpp Boost_Echo_Client/src/main.cpp Boost_Echo_Client/src/main.h)
