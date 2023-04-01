#pragma once

#include "DayTable.h"
#include "Page.h"

#include <windows.h>
#include <conio.h>

#include <iostream>
#include <regex>

class WeatherApp {
public:
    explicit WeatherApp() {
        std::vector<std::string> cities = {"Moscow"}; // , "Saint Petersburg", "Kaliningrad"
        pages_.reserve(cities.size());

        for (const std::string& i : cities) {
            pages_.push_back(new Page(i));
        }
    }

    void Run() {
        bool work = true;
        pages_[cur_page]->Show();

        while (work) {
            int key = getch();
            switch (key) {
                case 27: // ESC
                    work = false;
                    break;
                case 43: // +
                    pages_[cur_page]->ShowDay();
                    break;
                case 110: // n
                    system("cls");
                    pages_[cur_page]->clear();
                    ++cur_page %= pages_.size();
                    pages_[cur_page]->Show();
                    break;
                case 112: // p
                    system("cls");
                    pages_[cur_page]->Show();
                    break;
                case 45: // -
//                    pages_[cur_page]->ShowDay();
                    break;
                default:
                    std::cout << key << std::endl;
            }
        }
    }

    ~WeatherApp() {
        for (Page* i : pages_) {
            delete i;
        }
    }

private:
    std::vector<Page*> pages_;

    uint16_t cur_page = 0;
};