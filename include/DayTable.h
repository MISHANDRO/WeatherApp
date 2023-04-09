#pragma once

#include "ColorStr.h"

#include <windows.h>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <codecvt>


class DayTable {
public:
    static void SetColumnWidth(uint16_t n);

    static void PrintInfo(const std::string& title_, const std::vector<std::vector<ColorStr>>& column_texts);

private:
    static uint16_t GetAllWidth();

    static void PrintLine(uint16_t& cur, const ColorStr& title_ = ColorStr());
    static void PrintMany(uint16_t n, char ch);

    static void PrintMany(uint16_t n, const std::string& str);

    static uint16_t GetCenterPos(uint16_t width_all, const ColorStr& str);

    static const uint16_t count_column_ = 4;
    static const uint16_t count_row_ = 2;

    static inline uint16_t width_column_ = 40;
    static inline std::vector<ColorStr> column_names_;

    static inline std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
};
