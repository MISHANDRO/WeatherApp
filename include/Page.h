#pragma once

#include "Messages.h"
#include "DayTable.h"
#include "../WeatherManager/WeatherManager.h"

#include <iostream>
#include <regex>

class Page : public WeatherManager {
public:

    explicit Page(const std::string& city);
    void Show(bool default_ = true);

    void ShowDay();
    void DeleteDay();

    void ShowAllDay();
    void DeleteAllDay();

    void Update();
    static void SetDefaultDays(uint16_t val);

private:

    void ClearIterator();
    void PrintStatus() const;

    std::list<Day>::const_iterator cur_index;
    static inline uint16_t default_days_ = 3;
};
