#pragma once

#include <windows.h>

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <algorithm>

#define PREFIX std::string("&")

#define CM_BLACK (PREFIX + '0')
#define CM_DARK_BLUE (PREFIX + '1')
#define CM_DARK_GREEN (PREFIX + '2')
#define CM_TEAPOT_BLUE (PREFIX + '3')
#define CM_RED (PREFIX + '4')
#define CM_VIOLET (PREFIX + '5')
#define CM_YELLOW (PREFIX + '6')
#define CM_WHITE (PREFIX + '7')
#define CM_GRAY (PREFIX + '8')
#define CM_BLUE (PREFIX + '9')
#define CM_GREEN (PREFIX + ':')
#define CM_POOL_BLUE (PREFIX + ';')
#define CM_DULL_RED (PREFIX + '<')
#define CM_INDIGO (PREFIX + '=')
#define CM_DULL_YELLOW (PREFIX + '>')
#define CM_LIGHT_WHITE (PREFIX + '?')

#define CM_BACKGROUND_DARK_BLUE (PREFIX + '@')
#define CM_BACKGROUND_DARK_GREEN (PREFIX + 'P')
#define CM_BACKGROUND_RED (PREFIX + 'p')
#define CM_BACKGROUND_VIOLET (PREFIX + static<char>(80))
#define CM_BACKGROUND_YELLOW (PREFIX + static<char>(96))
#define CM_BACKGROUND_WHITE (PREFIX + static<char>(112))

class ColorStr {
public:
    ColorStr();
    ColorStr(const ColorStr& other);

    explicit ColorStr(std::string str_);

    ColorStr& operator=(const std::string& str_);

    [[nodiscard]] size_t size() const;

    static void SetEspecially(bool val);

    std::string str;
private:
    static inline bool especially = false;
};

std::ostream& operator<<(std::ostream& os, const ColorStr& str);
