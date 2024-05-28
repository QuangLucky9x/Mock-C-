#ifndef MP3_H
#define MP3_H

#include <string>
#include <filesystem>
#include <iostream>
#include "filename_utils.h"

class MP3 {
public:
    MP3(const std::string& path);
    std::string getName() const;
    std::string getPath() const;

private:
    std::string name;
    std::string path;
    void extractName(); // Function to extract the file name from the path
};

#endif // MP3_H
