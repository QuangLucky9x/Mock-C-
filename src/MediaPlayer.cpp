#include "MediaPlayer.h"
#include <iostream>
#include <chrono>
#include <thread>

MediaPlayer::MediaPlayer() : playing(false), paused(false), volume(128) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

MediaPlayer::~MediaPlayer() {
    stop();
    Mix_CloseAudio();
    SDL_Quit();
}

void MediaPlayer::play(const std::string& path) {
    std::cout<< "Playing: "<< getFileNameFromPath(path) <<std::endl;
    stop(); // Ensure any previous music is stopped
    playing = true;
    paused = false;
 //   std::cout << "Playing: " << getName() << " from " << song.getPath() << std::endl;
    musicThread = std::thread(&MediaPlayer::musicThreadFunc, this, path);
}

void MediaPlayer::stop() {
    if (playing) {
        playing = false;
        if (musicThread.joinable()) {
            musicThread.join();
        }
    }
}

void MediaPlayer::pause() {
    if (playing && !paused) {
        Mix_PauseMusic();
        paused = true;
    }
}

void MediaPlayer::resume() {
    if (playing && paused) {
        Mix_ResumeMusic();
        paused = false;
    }
}

void MediaPlayer::setVolume(int vol) {
    volume = vol;
    Mix_VolumeMusic(volume);
}

bool MediaPlayer::isPlaying() const {
    return playing;
}

void MediaPlayer::printMetadata(const std::string& path) {
    try {
        TagLib::FileRef f(path.c_str());
        if(!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            std::cout << "Title  : " << tag->title() << std::endl;
            std::cout << "Artist : " << tag->artist() << std::endl;
            std::cout << "Album  : " << tag->album() << std::endl;
            std::cout << "Year   : " << tag->year() << std::endl;
            std::cout << "Comment: " << tag->comment() << std::endl;
            std::cout << "Track  : " << tag->track() << std::endl;
            std::cout << "Genre  : " << tag->genre() << std::endl;
        } else {
            std::cerr << "Failed to read metadata for " << path << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception while reading metadata: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception while reading metadata" << std::endl;
    }
}

int MediaPlayer::getMusicDuration(const std::string& path) {
    TagLib::FileRef f(path.c_str());
    if (!f.isNull() && f.audioProperties()) {
        return f.audioProperties()->length();
    }
    return 0;
}
void MediaPlayer::playAllList(const PlayList& PlayList) {
    std::vector<MP3> songs = PlayList.getSongs();
    for (const MP3& song : songs) {
        std::cout << "Song list: " << song.getName() << " from " << song.getPath() << std::endl;
        // Your code to play the song goes here
        play(song.getPath());
    }
}
void MediaPlayer::musicThreadFunc(const std::string& path) {
    try {
        Mix_Music* music = Mix_LoadMUS(path.c_str());
        if (!music) {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            playing = false;
            return;
        }

        Mix_VolumeMusic(volume);
        Mix_PlayMusic(music, 1);

        int totalDuration = getMusicDuration(path);
        int currentTime = 0;

        // while (playing && Mix_PlayingMusic()) {
        //     std::this_thread::sleep_for(std::chrono::seconds(1));
        //     currentTime = totalDuration - (Mix_PlayingMusic() ? Mix_GetMusicPosition(music) : 0);
        //     std::cout<< "Playing: "<< getFileNameFromPath(path);
        //     std::cout << " - Current Time: " << currentTime << " / " << totalDuration << " seconds\r";
        //     std::cout.flush();
        // }

        Mix_FreeMusic(music);
    } catch (const std::exception& e) {
        std::cerr << "Exception in music thread: " << e.what() << std::endl;
        playing = false;
    } catch (...) {
        std::cerr << "Unknown exception in music thread" << std::endl;
        playing = false;
    }
}

void MediaPlayer::setMetadata(const std::string& path, const std::string& title, const std::string& artist, const std::string& album, int year, const std::string& comment, int track, const std::string& genre) {
    try {
        TagLib::FileRef f(path.c_str());
        if(!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            if (!title.empty()) tag->setTitle(title);
            if (!artist.empty()) tag->setArtist(artist);
            if (!album.empty()) tag->setAlbum(album);
            if (year != 0) tag->setYear(year);
            if (!comment.empty()) tag->setComment(comment);
            if (track != 0) tag->setTrack(track);
            if (!genre.empty()) tag->setGenre(genre);

            f.save();
            std::cout << "Metadata updated successfully." << std::endl;
        } else {
            std::cerr << "Failed to read metadata for " << path << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception while updating metadata: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception while updating metadata" << std::endl;
    }
}

int MediaPlayer::findMP3FileIndex( std::string& filePath, const std::vector<std::string>& filePaths) {
    for (size_t i = 0; i < filePaths.size(); i++) {
        if (filePaths[i] == filePath) {
            return i;
        }
    }
    return -1;
}

void MediaPlayer::next( std::string& filePath, const std::vector<std::string>& filePaths){
    int currentIndex = findMP3FileIndex(filePath,filePaths);
    if (currentIndex <filePaths.size()-1){

        filePath = filePaths[currentIndex+1];
         std::cout << currentIndex << " and " << filePath << std::endl;
    }
    else {
        filePath = (filePaths[0]);
       std::cout << currentIndex << " and " << filePath << std::endl;
    }
std::cout << currentIndex << " and " << filePath << std::endl;
    play(filePath);
};

void MediaPlayer::previous( std::string& filePath, const std::vector<std::string>& filePaths){
    int currentIndex = findMP3FileIndex(filePath,filePaths);
    if (currentIndex >0){
        filePath = (filePaths[currentIndex-1]);
    }
    else {
        filePath = (filePaths[filePaths.size()-1]);
    }
    play(filePath);
};





