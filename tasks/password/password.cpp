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
    for (size_t i = 0; i < password.size(); ++i) {
        if (static_cast<char>(min_code) > password[i] || static_cast<char>(max_code) < password[i]) {
            return false;
        } else if (std::isupper(password[i])) {
            has_upper = true;
        } else if (std::islower(password[i])) {
            has_lower = true;
        } else if (std::isdigit(password[i])) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }
    if (static_cast<int>(has_upper) + static_cast<int>(has_lower) + static_cast<int>(has_digit) +
            static_cast<int>(has_other) < min_num_of_classes) {
        return false;
    }
    return true;
}

