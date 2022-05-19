#include <fstream>
#include <iostream>
#include <sstream>


std::string readFile(std::string fn) {
    std::ifstream inFile;
    inFile.open(fn);

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    inFile.close();
    std::string str = strStream.str();
    strStream.clear();


    return strStream.str();
}