#include "password.h"

bool ValidatePassword(const std::string& password) {
    const size_t min_length = 8;
    const size_t max_length = 14;
    const int min_code = 33;
    const int max_code = 126;
    const int min_num_of_classes = 3;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_other = false;
    if (password.size() < min_length || password.size() > max_length) {
        return false;
    }
    for (const auto& elem : password) {
        if (static_cast<char>(min_code) > elem || static_cast<char>(max_code) < elem) {
            return false;
        } else if (std::isupper(elem)) {
            has_upper = true;
        } else if (std::islower(elem)) {
            has_lower = true;
        } else if (std::isdigit(elem)) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }
    return has_upper + has_lower + has_digit + has_other >= min_num_of_classes;
}
