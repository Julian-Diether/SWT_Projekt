
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "libraries/utf8library/source/utf8.h"

std::string myvalidateutf8(std::string str);

int main() {
    std::string str = "Genre:;$% *+~ - ??{[]}?";
    //std::getline(std::cin, str);
    std::cout << myvalidateutf8(str) << std::endl;
}

std::string myvalidateutf8(std::string str) {
    //https://github.com/nemtrif/utfcpp
    
    std::string temp;
    utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));

    std::replace(temp.begin(), temp.end(), '[', '?');
    std::replace(temp.begin(), temp.end(), ']', '?');
    std::replace(temp.begin(), temp.end(), '{', '?');
    std::replace(temp.begin(), temp.end(), '}', '?');
    return temp;
}  