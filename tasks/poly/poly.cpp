#include "poly.h"

Poly::Poly() {
    coefficients_ = {};
}

Poly::Poly(const std::vector<int64_t> &coefficients) {
    for (size_t pow = 0; pow < coefficients.size(); ++pow) {
        if (coefficients[pow] != 0) {
            coefficients_[pow] = coefficients[pow];
        }
    }
}

Poly::Poly(const std::vector<std::pair<int64_t, int64_t>> &coefficients) {
    for (const auto &[pow, c] : coefficients) {
        if (c != 0) {
            coefficients_[pow] = c;
        }
    }
}
int64_t FastPow(int64_t x, int64_t pow) {
    if (pow == 0) {
        return 1;
    }
    if (pow == 1) {
        return x;
    }
    int64_t res = FastPow(x, pow / 2);
    if (pow % 2 == 0) {
        return res * res;
    }
    return x * res * res;
}
int64_t Poly::operator()(const int64_t &x) const {
    int64_t sum = 0;
    for (const auto &[pow, c] : coefficients_) {
        sum += c * FastPow(x, pow);
    }
    return sum;
}

Poly Poly::operator+(const Poly &poly) const {
    Poly result;
    for (const auto &[pow, c1] : coefficients_) {
        int64_t c_res = c1 + poly.coefficients_.at(pow);
        if (c_res != 0) {
            result.coefficients_[pow] = c_res;
        }
    }
    return result;
}

Poly Poly::operator-(const Poly &poly) const {
    Poly result;
    for (const auto &[pow, c1] : coefficients_) {
        int64_t c_res = c1 - poly.coefficients_.at(pow);
        if (c_res != 0) {
            result.coefficients_[pow] = c_res;
        }
    }
    return result;
}

Poly Poly::operator-() const {
    Poly result;
    for (const auto &[pow, c] : coefficients_) {
        result.coefficients_[pow] = -c;
    }
    return result;
}

void Poly::operator+=(const Poly &poly) {
    for (const auto &[pow, c1] : poly.coefficients_) {
        coefficients_[pow] += c1;
        if (coefficients_[pow] == 0) {
            coefficients_.erase(pow);
        }
    }
}

void Poly::operator-=(const Poly &poly) {
    for (const auto &[pow, c1] : poly.coefficients_) {
        coefficients_[pow] -= c1;
        if (coefficients_[pow] == 0) {
            coefficients_.erase(pow);
        }
    }
}

bool Poly::operator==(const Poly &poly) const {
    if (poly.coefficients_.size() != coefficients_.size()) {
        return false;
    }
    for (const auto &[pow, c] : coefficients_) {
        if (poly.coefficients_.at(pow) != c) {
            return false;
        }
    }
    return true;
}

bool Poly::operator!=(const Poly &poly) const {
    if (poly.coefficients_.size() != coefficients_.size()) {
        return true;
    }
    for (const auto &[pow, c] : coefficients_) {
        if (poly.coefficients_.at(pow) != c) {
            return true;
        }
    }
    return false;
}

Poly Poly::operator*(const Poly &poly) const {
    Poly result;
    for (const auto &[pow1, c1] : coefficients_) {
        for (const auto &[pow2, c2] : poly.coefficients_) {
            result.coefficients_[pow1 + pow2] += c1 * c2;
        }
    }
    for (const auto &[pow, c] : result.coefficients_) {
        if (c == 0) {
            result.coefficients_.erase(pow);
        }
    }
    return result;
}

void Poly::operator*=(const Poly &poly) {
    Poly result;
    for (const auto &[pow1, c1] : coefficients_) {
        for (const auto &[pow2, c2] : poly.coefficients_) {
            result.coefficients_[pow1 + pow2] += c1 * c2;
        }
    }
    for (const auto &[pow, c] : result.coefficients_) {
        if (c == 0) {
            result.coefficients_.erase(pow);
        }
    }
    coefficients_ = result.coefficients_;
}

std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    os << "y = ";
    if (poly.coefficients_.empty()) {
        os << 0;
        return os;
    }
    auto it_last = (--poly.coefficients_.end());
    os << it_last->second;
    if (it_last->first != 0) {
        os << "x^" << it_last->first;
    }
    for (auto it = (--poly.coefficients_.end()); it != poly.coefficients_.begin(); --it) {
        os << ' ';
        int64_t pow = (--it)->first;
        int64_t c = (--it)->second;
        os << (c > 0 ? "+ " : "- ") << std::abs(c);
        if (pow != 0) {
            os << "x^" << pow;
        }
    }
    return os;
}