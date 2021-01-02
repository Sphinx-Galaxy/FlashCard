#include "FileHandler.h"

#include <fstream>

#ifdef DEBUG
#include <iostream>
#include <stdexcept>
#endif // DEBUG

string FileHandler::import_cards(const string &filename) {
    ifstream ifs(filename, std::ios::binary);

#ifdef DEBUG
    if(ifs.is_open() == false)
        throw std::invalid_argument("File not found!");
#endif // DEBUG

    string buffer((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    ifs.close();

    return buffer;
}

void FileHandler::export_cards(const string &filename, const string &content) {
    std::ofstream ofs(filename, std::ios::binary);

#ifdef DEBUG
    if(ofs.is_open() == false)
        throw std::invalid_argument("File not found!");
#endif // DEBUG

    ofs << content;
    ofs.close();
}

bool FileHandler::is_valid(const string &filename) {
    ifstream f(filename.c_str());
    return f.good();
}
