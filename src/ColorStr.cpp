#include "ColorStr.h"

#include <codecvt>

std::vector<std::string> split(const std::string& input, const std::string& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}

ColorStr::ColorStr() = default;
ColorStr::ColorStr(const ColorStr& other) = default;

ColorStr::ColorStr(std::string str_)
    : str(std::move(str_))
{}

ColorStr& ColorStr::operator=(const std::string& str_) {
    this->str = str_;
    return *this;
}

size_t ColorStr::size() const {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

    std::u32string u32str = converter.from_bytes(str);

    size_t res = u32str.size() - std::count(u32str.begin(), u32str.end(), '&') * 2;
    if (especially) {
        for (const char32_t &ch: u32str) {
            if (converter.to_bytes(ch).size() >= 3) {
                ++res;
            }
        }
    }

    return res;
}

void ColorStr::SetEspecially(bool val) {
    especially = val;
}

std::ostream& operator<<(std::ostream& os, const ColorStr& str) {
    std::vector<std::string> splits = split(str.str, PREFIX);
    os << splits[0];
    for (int j = 1; j < splits.size(); j++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), splits[j][0] - '0');
        os << splits[j].substr(1);
    }

    return os;
}