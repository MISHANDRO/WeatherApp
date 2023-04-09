#pragma once

#include "ColorStr.h"

#include "parser.h"

#include <unordered_map>
#include <string>
#include <vector>

class Messages {
public:
    static void Init(const std::string& language);

    static ColorStr header(const std::string& str);
    static ColorStr max_days(const std::string& str);
    static ColorStr error_city(const std::string& str);

    static inline ColorStr wait;
    static inline ColorStr header_;
    static inline ColorStr input;

    static inline ColorStr max_days_;
    static inline ColorStr error_weather;
    static inline ColorStr error_city_;
    static inline ColorStr update_error_info;
    static inline ColorStr error_network;

    static inline std::string font_family;
};
