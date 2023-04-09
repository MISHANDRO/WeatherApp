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

    static const inline std::vector<std::string> partly_sun = {
            "&6   \\__|/       &7",
            "&6  (     )      &7",
            "&6-(      &?.--.   &7",
            "&6  (__&?.-(    ). &7",
            "&6  / &?(___.__)__)&7",
    };


    static const inline std::vector<std::string> sun = {
            "&6   \\__|/   &7",
            "&6  (     )  &7",
            "&6-(       )-&7",
            "&6  (_____)  &7",
            "&6  /  |  \\  &7",
    };

    static const inline std::vector<std::string> snow = {
            "&?   .-.   &7",
            "&?  (   ). &7",
            "&? (___(__)&7",
            "&9 * * * * &7",
            "&9* * * *  &7",
    };

    static const inline std::vector<std::string> rain = {
            "&?   .-.   &7",
            "&?  (   ). &7",
            "&? (___(__)&7",
            "&9 / / / / &7",
            "&9/ / / /  &7",
    };

    static const inline std::vector<std::string> rain_snow = {
            "&?   .-.   &7",
            "&?  (   ). &7",
            "&? (___(__)&7",
            "&9 / * / * &7",
            "&9* / * /  &7",
    };

    static const inline std::vector<std::string> rain_shower = {
            "&8   .-.   &7",
            "&8  (   ). &7",
            "&8 (___(__)&7",
            "&9 // // / &7",
            "&9 // // /  &7",
    };

    static const inline std::vector<std::string> thunder = {
            "&8   .-.   &7",
            "&8  (   ). &7",
            "&8 (___(__)&7",
            "&9 /&6/  &9/ &6/ &7",
            "&9/ &6/ &9/  &6/  &7",
    };

    static const inline std::vector<std::string> fog = {
            "",
            "&8_ ─ _ ─ _ ─ &7",
            "&8 _ ─ _ ─ _ ─&7",
            "&8─ _ ─ _ ─ ─ &7",
            "&8 ─ _ _ ─ _ ─&7",
    };
};
