#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <iostream>
#include "MP3.h"



class PlayList {

private:
    std::vector<MP3> songs;
    std::string plName; 
public:

    void addSong(const MP3& song);
    void removeSong(const std::string& name);
    std::vector<MP3> getSongs() const;
    void setName(std::string playListName);
    std::string getName();


};

#endif // PLAYLIST_H
