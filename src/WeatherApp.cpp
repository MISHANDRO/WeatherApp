#include "WeatherApp.h"

#include "Page.h"

#include "parser.h"

#include <windows.h>

#include <iostream>
#include <regex>
#include <ctime>

WeatherApp::WeatherApp() {
    omfl::OmflConfiguration config("../resources/config.omfl");
    for (int i = 0; i < INT16_MAX; ++i) {
        omfl::Element cur = config.Get("main.cities")[i];
        if (!cur.IsString()) {
            break;
        }

        pages_.emplace_back(cur.AsString());
    }

    Messages::Init(config.Get("extra.language").AsStringOrDefault("ru"));

    DayTable::SetColumnWidth(40);

    cur_page = pages_.begin();
    frequency = config.Get("main.frequency").AsIntOrDefault(60 * 5);

    Page::SetMaxDays(config.Get("main.max_days").AsIntOrDefault(7));
    Page::SetDefaultDays(config.Get("main.default_days").AsIntOrDefault(3));

    SetConsoleOutputCP(CP_UTF8);
    std::string font_family = Messages::font_family;
    if (std::strcmp(font_family.c_str(), "default") != 0) {
        std::wstring wfont_family;
        wfont_family.assign(font_family.begin(), font_family.end());

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };
        GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
        fontInfo.dwFontSize.Y = static_cast<short>(config.Get("extra.font_size").AsIntOrDefault(16));
        wcscpy_s(fontInfo.FaceName, wfont_family.c_str());
        SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    }
}

void WeatherApp::Run() {

    bool work = true;

    if (pages_.empty()) {
        AddPage();
        cur_page = pages_.begin();
    }

    cur_page->Show();

    while (work) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // pause 50 milliseconds

        if (clock() / 1000 % frequency == 0) {
            cur_page->Update();
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            work = false;
        } else if (GetAsyncKeyState(107) & 0x8000) { // +
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                cur_page->ShowAllDay();
            } else {
                cur_page->ShowDay();
            }

        } else if (GetAsyncKeyState(109) & 0x8000) { // -
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                cur_page->DeleteAllDay();
            } else {
                cur_page->DeleteDay();
            }

        } else if (GetAsyncKeyState(78) & 0x8000) { // n
            system("cls");
            if (cur_page == pages_.begin()) {
                cur_page = pages_.end();
            }

            (--cur_page)->Show();
        } else if (GetAsyncKeyState(80) & 0x8000) { // p
            system("cls");
            if (++cur_page == pages_.end()) {
                cur_page = pages_.begin();
            }

            cur_page->Show();
        } else if (GetAsyncKeyState(85) & 0x8000) { // u
            cur_page->Update();
        } else if (GetAsyncKeyState(65) & 0x8000 && GetAsyncKeyState(VK_SHIFT) & 0x8000) {
            system("cls");
            AddPage();
            cur_page->Show();
        }
    }
}

void WeatherApp::AddPage() {
    std::cout << Messages::input;
    std::string city;
    std::cin >> city;

    pages_.emplace_back(city);
    cur_page = --pages_.end();
    system("cls");
}
