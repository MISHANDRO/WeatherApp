#include "Page.h"

#include "Messages.h"
#include "Pictures.h"
#include "DayTable.h"
#include "WeatherManager.h"

#include <iostream>

Page::Page(const std::string& city)
        : WeatherManager(city)
{}

void Page::Show(bool default_) {
    if (status() == RequestStatus::NotExecute) {
        system("cls");
        std::cout << Messages::wait << std::endl;
        Request();
        system("cls");
    }

    if (status() != RequestStatus::Success && !HaveInfo()) {
        system("cls");
        PrintStatus();

        return;
    }

    std::cout << Messages::header(city()) << std::endl << std::endl;

    std::vector<std::string> picture = Pictures::get(now().GetWeatherCode());
    uint16_t iterator = 0;
    for (const std::string& line : now().GetString(ColorMode::Prefix)) {
        std::cout << ColorStr("     " + picture[iterator++] + "     " + line) << std::endl;
    }

    ClearIterator();
    if (default_) {
        for (uint16_t i = 0; i < default_days_; ++i) {
            ShowDay();
        }
    }
}

void Page::ShowDay() {
    if (!HaveInfo()) {
        return;
    }

    if (cur_index == days_.cend()) {
        std::cout << Messages::max_days(std::to_string(max_days_)) << std::endl;
        return;
    }

    std::vector<std::vector<ColorStr>> info_;
    info_.reserve(4);

    for (const WeatherInfo* i : cur_index->GetParts()) {
        info_.emplace_back();
        std::vector<std::string> picture = Pictures::get(i->GetWeatherCode());
        uint16_t iterator = 0;

        for (const std::string& line : i->GetString(ColorMode::Prefix)) {
            info_.back().emplace_back(picture[iterator++] + "     " + line);
        }
    }

    DayTable::PrintInfo(cur_index->GetStrDate(), info_);

    ++cur_index;

    std::cout << std::endl;
}

void Page::DeleteDay() {
    if (!HaveInfo()) {
        return;
    }

    auto new_count = cur_index;
    if (--new_count == days_.cbegin()) {
        return;
    }

    system("cls");
    Show(false);
    while (cur_index != new_count) {
        ShowDay();
    }
}

void Page::ShowAllDay() {
    while (cur_index != days_.cend()) {
        ShowDay();
    }
}

void Page::DeleteAllDay() {
    if (cur_index == ++days_.cbegin()) {
        return;
    }

    system("cls");
    Show(false);
    ShowDay();
}

void Page::Update() {
    Request();
    system("cls");
    if (status() != RequestStatus::Success) {
        PrintStatus();
        std::cout << Messages::update_error_info << std::endl << std::endl;
    }

    if (default_days_ > max_days_) {
        default_days_ = max_days_;
    }

    Show();
}

void Page::SetDefaultDays(uint16_t val) {
    default_days_ = std::min(val, max_days_);
}


void Page::ClearIterator() {
    cur_index = days_.cbegin();
}

void Page::PrintStatus() const {
    switch (status()) {
        case NetworkError:
            std::cout << Messages::error_network << std::endl;
            break;
        case CityError:
            std::cout << Messages::error_city(city()) << std::endl;
            break;
        case WeatherError:
            std::cout << Messages::error_weather << std::endl;
            break;

    }
}