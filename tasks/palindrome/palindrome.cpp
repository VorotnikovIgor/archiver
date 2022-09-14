#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t l = 0;
    size_t r = str.size() - 1;
    while (l < r) {
        if (std::isspace(str[l])) {
            ++l;
        } else if (std::isspace(str[r])) {
            ++r;
        } else {
            if (str[r] != str[l]) {
                return false;
            }
            --r;
            --l;
        }
    }
    return true;
}
