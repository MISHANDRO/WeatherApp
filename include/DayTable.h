#pragma once

#include <vector>
#include <string>
#include <algorithm>

struct CHAR_ {
    static const char vertical = -77; // │
    static const char horizontal = -60; // ─

    static const char upper_left_corner = -38; // ┌
    static const char upper_right_corner = -65; // ┐
    static const char lower_left_corner = -64; // └
    static const char lower_right_corner = -39; // ┘

    static const char lower_corner = -63; // ┴
    static const char upper_corner = -62; // ┬

    static const char left_corner = -61; // ├
    static const char right_corner = -76; // ┤

    static const char crosshair = -59; // ┼
};

struct Position {
    uint16_t y;
    uint16_t x;
    uint16_t width;
};

class DayTable {
public:
    explicit DayTable(uint16_t width_column, const std::string& title,
                      const std::vector<std::string>& column_names,
                      const std::vector<std::vector<std::string>>& column_texts)
        : width_column_(width_column)
        , title_(" " + title + " ")
        , column_names_(column_names)
    {
        MakeDayInfo(column_texts);
    }

    [[nodiscard]] const std::vector<std::string>& GetText() const {
        return lines_;
    }

private:

    void MakeDayInfo(const std::vector<std::vector<std::string>>& column_texts) {

        lines_.resize(4 + column_texts[0].size() + 1, std::string(GetAllWidth(), ' '));

        for (uint16_t i = 0; i < count_column_; i++) {
            AddFragment(Position{1, static_cast<uint16_t>((width_column_ + 1) * i), width_column_}, {column_names_[i]});
        }

        for (uint16_t i = 0; i < count_column_; i++) {
            AddFragment(Position{3, static_cast<uint16_t>((width_column_ + 1) * i), width_column_}, column_texts[i]);
        }

        AddTitle();
    }

    static uint16_t GetCenterPos(uint16_t width_all, uint16_t width_el) {
        return (width_all - width_el) / 2;
    }

    static uint16_t GetCenterPos(uint16_t start_pos, uint16_t width_all, uint16_t width_el) {
        return (width_all - width_el) / 2 + start_pos + 1;
    }

    void AddFragment(const Position& pos, const std::vector<std::string>& text, bool is_title = false) {

        lines_[pos.y].replace(pos.x + 1, pos.width, pos.width, CHAR_::horizontal);
        lines_[pos.y + text.size() + 1].replace(pos.x + 1, pos.width, pos.width, CHAR_::horizontal);

        SetNewCorner(pos.y, pos.x, CHAR_::upper_left_corner);
        SetNewCorner(pos.y + text.size() + 1, pos.x, CHAR_::lower_left_corner);

        SetNewCorner(pos.y, pos.x + pos.width + 1, CHAR_::upper_right_corner);
        SetNewCorner(pos.y + text.size() + 1, pos.x + pos.width + 1, CHAR_::lower_right_corner);

        for (uint16_t i = 0; i < text.size(); i++) {
            size_t count_prefixes = std::count(text[i].begin(), text[i].end(), '&') * 2;
            lines_[i + pos.y + 1] += std::string(count_prefixes, ' ');

            size_t cur_x = std::count(lines_[i + pos.y + 1].begin(), lines_[i + pos.y + 1].end(), '&') * 2
                           + pos.x;

            uint16_t offset = GetCenterPos(cur_x, pos.width, text[0].size());
            lines_[i + pos.y + 1].replace(offset, text[i].size(), text[i]);

            lines_[i + pos.y + 1][cur_x] = CHAR_::vertical;
            lines_[i + pos.y + 1][cur_x + pos.width + count_prefixes + 1] = CHAR_::vertical;
        }

        if (is_title) {
            lines_[pos.y + 1][pos.x] = CHAR_::right_corner;
            lines_[pos.y + 1][pos.x + pos.width + 1] = CHAR_::left_corner;

            lines_[pos.y + 2][pos.x + (text[0].size() + 2) / 2] = CHAR_::upper_corner;
        }
    }

    void AddTitle() {
        uint16_t offset_title = GetCenterPos(lines_[0].size(), title_.size()) - 1;
        AddFragment(Position{0, offset_title, static_cast<uint16_t>(title_.size())}, {title_}, true);
    }

    void SetNewCorner(uint16_t pos_y, uint16_t pos_x, char border) {
        char char_ = lines_[pos_y][pos_x];
        char res = border;
        if (char_ < border) {
            std::swap(border, char_);
        }

        if (border == CHAR_::upper_right_corner && char_ == CHAR_::upper_left_corner) {
            // ┌ + ┐ = ┬
            res = CHAR_::upper_corner;
        } else if (border == CHAR_::lower_left_corner && char_ == CHAR_::lower_right_corner) {
            // ┘ + └ = ┴
            res = CHAR_::lower_corner;
        } else if (border == CHAR_::lower_left_corner && char_ == CHAR_::upper_left_corner) {
            // ┌ + └ = ├
            res = CHAR_::left_corner;
        } else if (border == CHAR_::upper_right_corner && char_ == CHAR_::lower_right_corner) {
            // ┘ + ┐ = ┤
            res = CHAR_::right_corner;
        }
        else if (char_ != ' ' && border != ' ') {
            res = CHAR_::crosshair;
        }

        lines_[pos_y][pos_x] = res;
    }

    [[nodiscard]] uint16_t GetAllWidth() const {
        return width_column_ * count_column_ + count_column_ + 1;
    }

    std::vector<std::string> lines_;

    static const uint16_t count_column_ = 4;

    const uint16_t width_column_;
    const std::string title_;
    const std::vector<std::string> column_names_;


};