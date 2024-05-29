#include "MP3.h"
#include <iostream>
#include <filesystem>



MP3::MP3(const std::string& path) : path(path), name(getFileNameFromPath(path)) {}

std::string MP3::getName() const {
    return name;
}

std::string MP3::getPath() const {
    return path;
}


