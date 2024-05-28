#include "../include/manager.h"
#include "../include/filename_utils.h"
#include <iostream>
#include <vector>

static std::string pathMP3;

void Manager:: homePage(){
    while (1){
    std::cout << "What do you want to do "<<std::endl;
        std::cout<< "Open a folder      -Press [1]"<<std::endl;
        std::cout<< "Open the playlist  -Press [2]"<<std::endl;
        std::cout<< "Quit               -Press [0]"<<std::endl;
         std::string command;
        std::getline(std::cin, command);
        if (command == "0") {
            break;
        } else if (command == "1") {
            OpenFolder();
        } else if (command == "2") {
            
}
        else {
            std::cout<< "ERROR. Please inform again" <<std::endl;
        }
    }
};

void Manager::OpenFolder(){
    bool state = true;
    while (state){
        if (state ==false){
            break;
        }
    std::cout<< "Input your folder" << std::endl;
    std::string command;
    std::getline(std::cin, command);
    std::vector MPList =listMP3Files(command);
    bool* check =&state;
    ProcessingFolder(MPList, check);
    
    }
};


void Manager::ProcessingFolder(std::vector<std::string>& MPList, bool* check){
    while(check){
    printMP3FileNames(MPList);
     std::cout<< "1.Play a song - Input song name" << std::endl 
              << "2.Quit        - PRESS [0]"<<std::endl
              << "3.Go back     - PRESS [1]" << std::endl;
    std::string command;
    std::getline(std::cin, command);
    if (command == "0") {
        *check = false;
            break;
        }
        else if (command =="1"){
            break;
        }
         else {
            
    playMP3FileByName(command,MPList);
        }

    }
};


void Manager::playMP3FileByName( std::string& fileName, 
 std::vector<std::string>& filePaths){
    
    for ( std::string& filePath : filePaths) {
        if (getFileNameFromPath(filePath) == fileName) {
            PlayClient(filePath,filePaths);
            
        }
    }
    std::cerr << "File not found: " << fileName << std::endl;

};

void Manager::PlayClient( std::string& filePath, const std::vector<std::string>& filePaths){
    pathMP3 =filePath;
    player.play(pathMP3);
    while (1){
    std::cout << "Commands: "      <<std::endl;
        std::cout<< "1. pause               2. resume"         <<std::endl;
        std::cout<< "3. next                4. previous"         <<std::endl;
        std::cout<< "5. volume <0-128>      6. metadata "<<std::endl;
        std::cout<< "7. setmetadata  <title> <artist> <album> <year> <comment> <track> <genre>"<<std::endl;
        std::cout<< "8. quit"<<std::endl;

         std::string command;
        std::getline(std::cin, command);

        if (command == "quit") {
            player.stop();
            break;
        } else if (command == "pause") {
            player.pause();
        } else if (command == "resume") {
            player.resume();
        } else if (command.find("volume ") == 0) {
            int vol = std::stoi(command.substr(7));
            player.setVolume(vol);
        } else if (command == "next") {
            player.next(pathMP3,filePaths);
            
        } else if (command == "previous") {
            player.previous(pathMP3,filePaths);
            
        } else if (command.find("metadata") == 0) {
           // std::string path = command.substr(9);
            player.printMetadata(pathMP3);
        } else if (command.find("setmetadata") == 0) {
           std::istringstream iss(command.substr(12));
            std::string path, title, artist, album, comment, genre;
            int year = 0, track = 0;
            iss >> title >> artist >> album >> year >> comment >> track >> genre;
            player.setMetadata(pathMP3, title, artist, album, year, comment, track, genre);
        } else {
            std::cout << "Unknown command\n";
        }
    }

}
void Manager:: newPlayList(){
    while(1){
    std::cout<<"Press [0] to quit or New play list name: " <<std::endl;
    std::string command;
        std::getline(std::cin, command);
        if(command =="0"){
            break;
        }
        else {
            PlayList newPL;
            PlayListFolder.push_back(newPL);
        }
 }
};

void Manager:: PlayListController(){
    while(1){
        showPlayList();
        std::cout<<"Open playlist    - Input playlist name"<<std::endl;
        std::cout<<"New play list    - Press [1]"<<std::endl;
        std::cout<<"Quit             - Press [0]"<<std::endl;

         std::string command;
        std::getline(std::cin, command);

        if (command == "0") {
            break;
        } else if (command == "1") {
            newPlayList();
        } else{

        }
    }
};



void Manager:: showPlayList(){
    int a = 0;
    for ( auto& obj : PlayListFolder) {
        std::cout << obj.getName() << std::endl;
        a++;
    }
    if(a==0){std::cout<< "There is no existed playlist"<<std::endl;}
}

void Manager:: MediaPlay(){
    while (1){
    std::cout << "Commands: "      <<std::endl;
        std::cout<< "1. play <path>"   <<std::endl;
        std::cout<< "2. stop"          <<std::endl;
        std::cout<< "3. pause"         <<std::endl;
        std::cout<< "4. resume"        <<std::endl;
        std::cout<< "5. volume <0-128>"<<std::endl;
        std::cout<< "6. metadata <path>"<<std::endl;
        std::cout<< "7. setmetadata <path> <title> <artist> <album> <year> <comment> <track> <genre>"<<std::endl;
        std::cout<< "8. quit"<<std::endl;

         std::string command;
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        } else if (command.find("play ") == 0) {
            std::string path = command.substr(5);
            player.play(path);
        } else if (command == "stop") {
            player.stop();
        } else if (command == "pause") {
            player.pause();
        } else if (command == "resume") {
            player.resume();
        } else if (command.find("volume ") == 0) {
            int vol = std::stoi(command.substr(7));
            player.setVolume(vol);
        } else if (command.find("metadata ") == 0) {
            std::string path = command.substr(9);
            player.printMetadata(path);
        } else if (command.find("setmetadata ") == 0) {
            std::istringstream iss(command.substr(12));
            std::string path, title, artist, album, comment, genre;
            int year = 0, track = 0;
            iss >> path >> title >> artist >> album >> year >> comment >> track >> genre;
            player.setMetadata(path, title, artist, album, year, comment, track, genre);
        } else {
            std::cout << "Unknown command\n";
        }
    }
};

//===============PLAYLIST-------------------

