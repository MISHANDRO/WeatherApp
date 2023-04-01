#pragma once

#include "Pictures.h"
#include "DayTable.h"

#include <vector>
#include <cstdint>
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <regex>

struct WeatherInfo {
    uint16_t weather = 4;
    std::string temperature = "0";
    std::string wind_speed = "0";
    std::string wind_direction{char(25)};
    std::string pressure = "1000.0";
    std::string precipitation = "0.0";
    std::string precipitation_probability = "0";
};

std::vector<std::string> split(const std::string& input, const std::string& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}

class Day {
public:
    explicit Day(const std::string& date)
        : current_day(GetTm(date))
    {
        day_parts.reserve(4);
    }

    ~Day() {
        for (const WeatherInfo* wi : day_parts) {
            delete wi;
        }
    }

    void AddPart(const WeatherInfo* wi) {
        if (day_parts.size() == day_parts.capacity()) {
            return;
        }

        day_parts.push_back(wi);
    }

    void Show() {
        std::vector<std::vector<std::string>> info_;
        for (const WeatherInfo* i : day_parts) {
            std::vector<std::string> cur(5);
            std::vector<std::string> picture = Pictures.at(0);
            cur[0] = picture[0] + "   " + WeatherNames.at(i->weather);
            cur[1] = picture[1] + "   " + i->temperature + char(-8) + 'C';
            cur[2] = picture[2] + "   " + i->wind_direction + " " + i->wind_speed + " m/s";
            cur[3] = picture[3] + "   " + i->pressure + " mmHg";
            cur[4] = picture[4] + "   " + i->precipitation + " mm | " + i->precipitation_probability + "%";

            if (cur[0].size() > 25) {
                cur[0].resize(25);
                cur[0] += "...";
            }

            info_.push_back(cur);
        }

        DayTable d(30, GetStrDate(), {"Utro", "Day", "Vecher", "Night"}, info_);

        for (const std::string& i : d.GetText()) {
            std::vector<std::string> splits = split(i, R"(&)");
            std::cout << splits[0];
            for (int j = 1; j < splits.size(); j++) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), splits[j][0] - '0');
                std::cout << splits[j].substr(1);
            }

            std::cout << std::endl;
        }
    }


private:
    static std::tm GetTm(const std::string& date) {
        std::tm tm{};

        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M");
        std::time_t time = mktime(&tm);

        std::tm* res = std::localtime(&time);
        tm.tm_mon++;
        tm.tm_year += 1900;
        tm.tm_wday = res->tm_wday;

        return tm;
    }

    std::string GetStrDate() {
        return std::to_string(current_day.tm_wday) + " " + std::to_string(current_day.tm_mday) + "."
               + std::to_string(current_day.tm_mon) + "." + std::to_string(current_day.tm_year);
    }

    std::vector<const WeatherInfo*> day_parts;
    const std::tm current_day;
};
