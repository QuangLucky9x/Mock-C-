#ifndef FILENAME_UTILS_H
#define FILENAME_UTILS_H

#include <string>
#include <vector>

std::string getFileNameFromPath(const std::string& path);
std::vector<std::string> listMP3Files(const std::string& directoryPath);
void printMP3FileNames(const std::vector<std::string>& filePaths);

#endif // FILENAME_UTILS_H
