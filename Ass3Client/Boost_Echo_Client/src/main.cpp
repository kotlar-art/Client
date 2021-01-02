//
// Created by spl211 on 02/01/2021.
//

#include <iostream>
#include "main.h"

int main(){
    const short bufsize = 1024;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::string line(buf);
    int len=line.length();
}