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
include_directories(WeatherManager)

include_directories(labwork-6-MISHANDRO/lib)
add_subdirectory(labwork-6-MISHANDRO/lib)

add_executable(labwork_10_MISHANDRO main.cpp
        include/ColorStr.h               src/ColorStr.cpp
        include/DayTable.h               src/DayTable.cpp
        include/Pictures.h               src/Pictures.cpp
        include/Messages.h               src/Messages.cpp
        include/WeatherApp.h             src/WeatherApp.cpp
        include/Page.h                   src/Page.cpp
        WeatherManager/Day.h WeatherManager/Day.cpp

        WeatherManager/WeatherManager.h  WeatherManager/WeatherManager.cpp
        WeatherManager/WeatherInfo.h     WeatherManager/WeatherInfo.cpp

        labwork-6-MISHANDRO/lib/Element.h labwork-6-MISHANDRO/lib/Element.cpp
        labwork-6-MISHANDRO/lib/parser.h labwork-6-MISHANDRO/lib/parser.cpp
        )

target_link_libraries(labwork_10_MISHANDRO PRIVATE cpr::cpr)
target_link_libraries(labwork_10_MISHANDRO PRIVATE nlohmann_json::nlohmann_json)
