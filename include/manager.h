#ifndef MANAGER_H
#define MANAGER_H

#include "MP3.h"
#include "PlayList.h"
#include "MediaPlayer.h"
#include <iostream>
#include <vector>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include <thread>
#include <atomic>
#include "filename_utils.h"


class Manager{
    public: 
        Manager(){};
        void homePage();
        void MediaPlay();
        void OpenFolder();
        void playMP3FileByName( std::string& fileName, 
     std::vector<std::string>& filePaths);
        void ProcessingFolder(std::vector<std::string>& MPList, bool* check) 
;
        void PlayClient( std::string& filePath,const std::vector<std::string>& filePaths);
        void newPlayList();
        void showPlayList();
        void PlayListController();
        
    private:
        MediaPlayer player;
        std::vector <PlayList> PlayListFolder;
        
};

#endif