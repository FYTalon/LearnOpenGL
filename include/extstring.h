#ifndef EXTSTRING_H_
#define EXTSTRING_H_

#include <string>
#include <cstring>
#include <istream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> split(const std::string &str, const char skip){
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> array;
    while(std::getline(ss, item, skip)) {
        if(!item.empty())
            array.push_back(item);
    }
    return array;
}

#endif