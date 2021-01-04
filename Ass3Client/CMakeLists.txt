cmake_minimum_required(VERSION 3.17)
project(Ass3Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(Boost_Echo_Client/include)

add_executable(Ass3Client
        Boost_Echo_Client/include/connectionHandler.h
        Boost_Echo_Client/src/connectionHandler.cpp
        Boost_Echo_Client/src/echoClient.cpp
        Boost_Echo_Client/makefile Boost_Echo_Client/src/Client.cpp Boost_Echo_Client/include/Client.h Boost_Echo_Client/include/main.h Boost_Echo_Client/src/Task.cpp Boost_Echo_Client/include/Task.h Boost_Echo_Client/src/Writer.cpp Boost_Echo_Client/include/Writer.h Boost_Echo_Client/src/Reader.cpp Boost_Echo_Client/src/Reader.h)
