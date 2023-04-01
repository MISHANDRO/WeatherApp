#pragma once

#include "Day.h"

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <ctime>
#include <iostream>
#include <vector>


class WeatherManager {
public:
    explicit WeatherManager(std::string city)
        : city_(std::move(city))
    {
        days_.reserve(16);
    }

    ~WeatherManager() {
        for (Day* day : days_) {
            delete day;
        }
    }

    void create() {
        cpr::Response r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                   cpr::Parameters{{"name", city_}},
                                   cpr::Header{{"X-Api-Key", "nDiNfJvc76/eQPfcOD0FIw==wJV04TtRzRKbjUvM"}});

        nlohmann::json responseJson = nlohmann::json::parse(r.text);

        r = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                     cpr::Parameters{
                             {"latitude", std::to_string(static_cast<double>(responseJson[0]["latitude"]))},
                             {"longitude", std::to_string(static_cast<double>(responseJson[0]["longitude"]))},
                             {"hourly", "temperature_2m,relativehumidity_2m,"
                                        "precipitation_probability,precipitation,"
                                        "weathercode,surface_pressure,"
                                        "windspeed_10m,winddirection_10m"},
                             {"current_weather", "true"},
                             {"forecast_days", "16"},
                             {"windspeed_unit", "ms"},
                             {"timezone", "Europe/Moscow"}
                     });

        responseJson = nlohmann::json::parse(r.text);

        for (int i = 0; i < responseJson["hourly"]["time"].size(); i++) {
            if (i % 24 % 6 == 0) {

                if (i % 24 == 0) {
                    days_.push_back(new Day(responseJson["hourly"]["time"][i]));
                }

                auto* wi = new WeatherInfo{};

                if (responseJson["hourly"]["weathercode"][i].is_null()) {
                    days_.pop_back();
                    break;
                }

                responseJson["hourly"]["weathercode"][i].get_to(wi->weather);
                conv(wi->temperature, responseJson["hourly"]["temperature_2m"][i]);
                conv(wi->wind_speed, responseJson["hourly"]["windspeed_10m"][i]);
//                conv(wi->wind_direction, responseJson["hourly"]["winddirection_10m"][i]);
                conv(wi->pressure, responseJson["hourly"]["surface_pressure"][i]);
                wi->pressure = std::to_string(std::atof(wi->pressure.c_str()) * 0.75).substr(0, 3);

                conv(wi->precipitation, responseJson["hourly"]["precipitation"][i]);
                conv(wi->precipitation_probability, responseJson["hourly"]["precipitation_probability"][i]);

                days_.back()->AddPart(wi);
            }
        }

    }

    [[nodiscard]] std::string city() const {
        return city_;
    }

    [[nodiscard]] Day* GetDay(uint16_t n) const {
        return days_[n];
    }

private:

    template<typename T>
    void conv(std::string& obj, const T& inf) const {
        if (!inf.is_null()) {
            double tmp_double;
            short tmp = inf.get_to(tmp_double) * 10;
            obj = std::to_string(tmp / 10);

            if (tmp % 10) {
                obj += "." + std::to_string(tmp % 10);
            }
        }
    }

    std::string city_;
    WeatherInfo now_;
    std::vector<Day*> days_;
};
