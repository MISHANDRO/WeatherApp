#pragma once

#include "DayTable.h"
#include "Page.h"

#include "parser.h"

#include <windows.h>
#include <conio.h>

#include <iostream>
#include <regex>
#include <ctime>

class WeatherApp {
public:
    explicit WeatherApp();
    void Run();

private:

    void AddPage();

    uint16_t frequency;

    std::list<Page> pages_;
    std::list<Page>::iterator cur_page;
};
