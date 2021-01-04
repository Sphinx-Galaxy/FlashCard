#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
    public:
        static std::string import_cards(const std::string &filename);
        static void export_cards(const std::string &filename, const std::string &content);

        static bool is_valid(const std::string &filename);
};

#endif // FILEHANDLER_H
