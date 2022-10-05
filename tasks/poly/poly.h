#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <map>

class Poly {
    std::map<int64_t, int64_t> coefficients_;
public:
    Poly();
    Poly(const std::vector<int64_t> &);
    Poly(const std::vector<std::pair<int64_t, int64_t>> &);
    int64_t operator()(const int64_t &) const;
    Poly operator*(const Poly &) const;
    Poly operator+(const Poly &) const;
    Poly operator-(const Poly &) const;
    void operator-=(const Poly &);
    void operator+=(const Poly &);
    bool operator==(const Poly &) const;
    Poly operator-() const;
    bool operator!=(const Poly &) const;
    friend std::ostream &operator<<(std::ostream &os, const Poly&);
};
