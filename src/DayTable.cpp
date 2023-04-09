#include "DayTable.h"

#include "ColorStr.h"
#include "Day.h"

#include <vector>
#include <string>
#include <iostream>

struct BorderChars {

    constexpr static char vertical[] = "│";
    constexpr static char horizontal[] = "─";

    constexpr static char upper_left_corner[] = "┌";
    constexpr static char upper_right_corner[] = "┐";
    constexpr static char lower_left_corner[] = "└";
    constexpr static char lower_right_corner[] = "┘";

    constexpr static char lower_corner[] = "┴";
    constexpr static char upper_corner[] = "┬";

    constexpr static char left_corner[] = "├";
    constexpr static char right_corner[] = "┤";

    constexpr static char crosshair[] = "┼";
};



bool comparator(const ColorStr& i1, const ColorStr& i2) {
    return i1.size() < i2.size();
}

void DayTable::SetColumnWidth(uint16_t n) {
    width_column_ = n;
}

uint16_t DayTable::GetAllWidth() {
    return width_column_ * count_column_ + count_column_ + 1;
}

void DayTable::PrintInfo(const std::string& title_, const std::vector<std::vector<ColorStr>>& column_texts) {
    ColorStr title(' ' + title_ + ' ');

    uint16_t cur = 0;
    std::vector<int> offsets;
    offsets.reserve(width_column_);

    uint16_t offset = GetCenterPos(GetAllWidth() - 1, title);
    PrintMany(offset, ' ');

    std::cout << BorderChars::upper_left_corner;
    PrintMany(title.size(), BorderChars::horizontal);
    std::cout << BorderChars::upper_right_corner << std::endl;

    PrintMany(offset, ' ');

    std::cout << BorderChars::vertical
              << title
              << BorderChars::vertical << std::endl;


    PrintLine(cur, title);

    std::cout << BorderChars::vertical;
    uint16_t it = 0;
    for (auto& i : Day::time_parts) {
        ColorStr column_name(i);
        PrintMany(GetCenterPos(width_column_, column_name), ' ');
        std::cout << column_name;

        PrintMany(width_column_ - GetCenterPos(width_column_, column_name) - column_name.size(), ' ');
        std::cout << BorderChars::vertical;
        it++;
    }
    std::cout << std::endl;

    PrintLine(cur);

    for (const auto& column_text : column_texts) {
        ColorStr res  = *std::max_element(column_text.begin(), column_text.end(), comparator);
        offsets.push_back(GetCenterPos(width_column_, res));
    }

    for (int i = 0; i < column_texts[0].size(); ++i) {
        std::cout << BorderChars::vertical;

        uint16_t iterator = 0;
        for (auto& column_text : column_texts) {
            PrintMany(offsets[iterator], ' ');
            std::cout << column_text[i];

            PrintMany(width_column_ - offsets[iterator] - column_text[i].size(), ' ');
            std::cout << BorderChars::vertical;

            ++iterator;
        }

        std::cout << std::endl;
    }

    PrintLine(cur);
}

void DayTable::PrintLine(uint16_t& cur, const ColorStr& title_) {
    std::u32string line(GetAllWidth() - 2, converter.from_bytes(BorderChars::horizontal)[0]);
    char32_t border;

    switch(cur) {
        case 0: {
            std::cout << BorderChars::upper_left_corner;
            border = converter.from_bytes(BorderChars::upper_corner)[0];
            uint16_t title_offset = GetCenterPos(GetAllWidth() - 1, title_);
            line[title_offset - 1] = converter.from_bytes(BorderChars::lower_corner)[0];
            line[title_offset + title_.size()] = converter.from_bytes(BorderChars::lower_corner)[0];
        }
            break;
        case count_row_:
            std::cout << BorderChars::lower_left_corner;
            border = converter.from_bytes(BorderChars::lower_corner)[0];
            break;
        default:
            std::cout << BorderChars::left_corner;
            border = converter.from_bytes(BorderChars::crosshair)[0];
    }

    for (uint16_t i = 1; i < count_column_; ++i) {
        line[(width_column_ + 1) * i - 1] = border;
    }
    std::cout << converter.to_bytes(line);

    if (cur == 0) {
        std::cout << BorderChars::upper_right_corner;
    } else if (cur == count_row_) {
        std::cout << BorderChars::lower_right_corner;
    } else {
        std::cout << BorderChars::right_corner;
    }

    std::cout << std::endl;
    ++cur;
}

void DayTable::PrintMany(uint16_t n, char ch) {
    for (uint16_t i = 0; i < n; ++i) {
        std::cout << ch;
    }
}

void DayTable::PrintMany(uint16_t n, const std::string& str) {
    for (uint16_t i = 0; i < n; ++i) {
        std::cout << str;
    }
}

uint16_t DayTable::GetCenterPos(uint16_t width_all, const ColorStr& str) {
    return (width_all - str.size()) / 2;
}
