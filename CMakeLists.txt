cmake_minimum_required(VERSION 3.24)
project(labwork_10_MISHANDRO)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

if(WIN32) # Установите библиотеки DLL в тот же каталог, что и исполняемый файл в наборе Windows(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(include)

add_executable(labwork_10_MISHANDRO main.cpp
        include/DayTable.h
        include/Pictures.h
        include/WeatherManager.h
        include/WeatherApp.h
        include/Page.h
        include/Day.h)

target_link_libraries(labwork_10_MISHANDRO PRIVATE cpr::cpr)
target_link_libraries(labwork_10_MISHANDRO PRIVATE nlohmann_json::nlohmann_json)
