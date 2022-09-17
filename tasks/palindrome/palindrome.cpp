#include <cctype>
#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    auto l = str.begin();
    auto r = --str.end();
    while (l != str.end()) {
        if (std::isspace(*l)) {
            ++l;
        } else if (std::isspace(*r)) {
            --r;
        } else {
            if (*r != *l) {
                return false;
            }
            --r;
            ++l;
        }
    }
    return true;
}
