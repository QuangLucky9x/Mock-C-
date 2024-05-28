cmake_minimum_required(VERSION 3.10)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 and SDL2_mixer
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Find TagLib
find_package(Taglib REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${TAGLIB_INCLUDE_DIRS} include)

# Add source files
add_executable(main src/main.cpp src/mediaPlayer.cpp)

# Link SDL2, SDL2_mixer, and TagLib libraries
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${TAGLIB_LIBRARIES})
