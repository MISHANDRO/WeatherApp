#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class Pictures {
public:

    static const std::vector<std::string>& get(int n);

    static const inline std::vector<std::string> clouds = {
            "           ",
            "&?    .--.   &7",
            "&? .-(    ). &7",
            "&?(___.__)__)&7",
            "           "
    };

    static const inline std::vector<std::string> sun = {
            "&6   \\__|/   &7",
            "&6  (     )  &7",
            "&6-(       )-&7",
            "&6  (_____)  &7",
            "&6  /  |  \\  &7",
    };

    static const inline std::vector<std::string> snow = {
            "&?   .-.  &7",
            "&?  (   ).&7",
            "&? (___() &7",
            "&9 * * * *&7",
            "&9* * * * &7",
    };

    static const inline std::vector<std::string> rain = {
            "&?   .-.  &7",
            "&?  (   ).&7",
            "&? (___() &7",
            "&9 / / / /&7",
            "&9/ / / / &7",
    };
};
