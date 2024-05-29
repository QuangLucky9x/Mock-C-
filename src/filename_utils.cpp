#include "filename_utils.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::string getFileNameFromPath(const std::string& path) {
    fs::path p(path);
    return p.filename().string();
}

std::vector<std::string> listMP3Files(const std::string& directoryPath) {
    std::vector<std::string> mp3Files;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            mp3Files.push_back(entry.path().string());
        }
    }
    return mp3Files;
}
void printMP3FileNames(const std::vector<std::string>& filePaths) {
    std::cout << "MP3 files:" << std::endl;
    for (const std::string& path : filePaths) {
        std::cout << getFileNameFromPath(path) << std::endl;
    }

}


