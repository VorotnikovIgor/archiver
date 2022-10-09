#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <map>

class Poly {
private:
    std::map<uint64_t, int64_t> coefficients_;

public:
    Poly();
    Poly(const std::initializer_list<int64_t> &);
    Poly(const std::initializer_list<std::pair<uint64_t, int64_t>> &);
    int64_t operator()(const int64_t &) const;
    Poly operator*(const Poly &) const;
    Poly operator+(const Poly &) const;
    Poly operator-(const Poly &) const;
    Poly &operator-=(const Poly &);
    Poly &operator+=(const Poly &);
    Poly &operator*=(const Poly &);
    bool operator==(const Poly &) const;
    Poly operator-() const;
    bool operator!=(const Poly &) const;
    friend std::ostream &operator<<(std::ostream &os, const Poly &);
};
