#include "PlayList.h"
#include <algorithm> // for std::remove_if

void PlayList::addSong(const MP3& song) {
    songs.push_back(song);
}

void PlayList::removeSong(const std::string& name) {
    songs.erase(std::remove_if(songs.begin(), songs.end(), [&name](const MP3& song) {
        return song.getName() == name;
    }), songs.end());
}

std::vector<MP3> PlayList::getSongs() const {
    return songs;
}
void PlayList::setName(std::string playListName){
    plName = playListName;
}
std::string PlayList:: getName(){
    return plName;
}
