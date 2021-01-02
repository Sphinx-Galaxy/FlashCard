#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

using namespace std;

class FileHandler {
    public:
        static string import_cards(const string &filename);
        static void export_cards(const string &filename, const string &content);

        static bool is_valid(const string &filename);
};

#endif // FILEHANDLER_H
