#include "Messages.h"

#include "ColorStr.h"
#include "Day.h"
#include "WeatherInfo.h"

#include "parser.h"

#include <unordered_map>
#include <string>
#include <vector>

bool replace(ColorStr& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.str.find(from);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.str.replace(start_pos, from.length(), to);
    return true;
}


void Messages::Init(const std::string& language) {
    omfl::OmflConfiguration config("resources/languages.omfl");
    const omfl::Element& section = config.Get(language);

    std::vector<std::string> time_parts;
    time_parts.reserve(4);
    for (int i = 0; i < 4; ++i) {
        time_parts.emplace_back(section.Get("time_parts")[i].AsString());
    }

    std::vector<std::string> weekday_names;
    weekday_names.reserve(7);
    for (int i = 0; i < 7; ++i) {
        weekday_names.emplace_back(section.Get("weekday_names")[i].AsString());
    }

    std::vector<std::string> month_names;
    month_names.reserve(12);
    for (int i = 0; i < 12; ++i) {
        month_names.emplace_back(section.Get("month_names")[i].AsString());
    }

    Day::SetMessages(time_parts, weekday_names, month_names);

    wait = section.Get("wait").AsString();
    header_ = section.Get("header").AsString();
    input = section.Get("input").AsString();

    max_days_ = section.Get("max_days").AsString();
    error_weather = section.Get("error_weather").AsString();
    error_city_ = section.Get("error_city").AsString();
    update_error_info = section.Get("update_error_info").AsString();
    error_network = section.Get("error_network").AsString();

    WeatherInfo::SetDesignations(section.Get("wind_speed").AsString(), section.Get("mmHg").AsString(),
                                 section.Get("mm").AsString());

    std::vector<std::string> weather_names;
    time_parts.reserve(28);
    for (int i = 0; i < 28; ++i) {
        weather_names.emplace_back(section.Get("weather_names")[i].AsString());
    }

    WeatherInfo::SetWeatherNames(weather_names);

    ColorStr::SetEspecially(section.Get("especially").AsBoolOrDefault(false));
    font_family = section.Get("font_family").AsStringOrDefault("default");
}

ColorStr Messages::header(const std::string& str) {
    ColorStr res = header_;
    if (!replace(res, "%s", str)) {
        res.str += ' ' + str;
    }

    return res;
}

ColorStr Messages::max_days(const std::string& str) {
    ColorStr res = max_days_;
    if (!replace(res, "%d", str)) {
        res.str += ' ' + str;
    }

    return res;
}

ColorStr Messages::error_city(const std::string& str) {
    ColorStr res = error_city_;
    if (!replace(res, "%s", str)) {
        res.str += ' ' + str;
    }

    return res;
}
