#pragma once

#include "DayTable.h"
#include "WeatherManager.h"
#include "Pictures.h"

#include <iostream>
#include <regex>

class Page {
public:

    Page(const std::string& city)
        : wm_(WeatherManager(city))
    {
        wm_.create();
    }

    void Show() {
        std::cout << wm_.city() << std::endl << std::endl;
        ShowDay();
    }

    void ShowDay() {
        wm_.GetDay(cur_index)->Show();
        ++cur_index;

        std::cout << std::endl;
    }

    void clear() {
        cur_index = 0;
    }

private:



    WeatherManager wm_;

    uint16_t cur_index = 0;
};