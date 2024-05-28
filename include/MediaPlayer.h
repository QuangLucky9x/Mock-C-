#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <iostream>
#include <vector>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include <thread>
#include <atomic>
#include "PlayList.h"


class MediaPlayer {
public:
    MediaPlayer();
    ~MediaPlayer();
    
    void playAllList(const PlayList& PlayList);
    void play(const std::string& path);
    void stop();
    void pause();
    void resume();
    void setVolume(int volume);
    bool isPlaying() const;
    void printMetadata(const std::string& path);
    void setMetadata(const std::string& path, const std::string& title, 
        const std::string& artist, const std::string& album, int year, const std::string& comment, int track, const std::string& genre);
    int findMP3FileIndex( std::string& filePath, const std::vector<std::string>& filePaths);

    void next( std::string& filePath, const std::vector<std::string>& filePaths);
    void previous( std::string& filePath, const std::vector<std::string>& filePaths);
    

private:
    void musicThreadFunc(const std::string& path);
    int getMusicDuration(const std::string& path);

    std::thread musicThread;
    std::atomic<bool> playing;
    std::atomic<bool> paused;
    std::atomic<int> volume;
};

#endif // MEDIAPLAYER_H