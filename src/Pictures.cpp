#include "Pictures.h"

#include <vector>
#include <string>

const std::vector<std::string>& Pictures::get(int n) {
    if (0 <= n && n <= 1) {
        return sun;
    } else if (n <= 48) {
        return clouds;
    } else if ((51 <= n && n <= 57) || (66 <= n && n <= 77) || (85 <= n && n <= 86)) {
        return snow;
    } else {
        return rain;
    }
}
