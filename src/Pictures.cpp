#include "Pictures.h"

#include <vector>
#include <string>

const std::vector<std::string>& Pictures::get(int n) {
    if (n == 0) {
        return sun;
    } else if (n <= 2) {
        return partly_sun;
    } else if (n == 3) {
        return clouds;
    } else if (n <= 65) {
        return rain;
    } else if (n <= 67) {
        return rain_snow;
    } else if (n <= 77) {
        return snow;
    } else if (n <= 82) {
        return rain_shower;
    } else if (n <= 86) {
        return snow;
    } else {
        return thunder;
    }
}
