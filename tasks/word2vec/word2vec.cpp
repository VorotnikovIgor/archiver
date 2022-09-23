#include <cmath>
#include "word2vec.h"

int64_t ScalarProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return sum;
}

int64_t sign(int64_t x) {
    if (x > 0) {
        return 1;
    } else if (x == 0) {
        return 0;
    } else {
        return -1;
    }
}

bool ValGreater(const std::pair<std::pair<int64_t, int64_t>, size_t>& x,
                       const std::pair<std::pair<int64_t, int64_t>, size_t>& y) {
    int64_t val1 = x.first.first * x.first.first * y.first.second * sign(x.first.first);
    int64_t val2 = y.first.first * y.first.first * x.first.second * sign(y.first.first);
    return (val1 > val2);
}

bool ValEqual(const std::pair<std::pair<int64_t, int64_t>, size_t>& x,
                const std::pair<std::pair<int64_t, int64_t>, size_t>& y) {
    int64_t val1 = x.first.first * x.first.first * y.first.second * sign(x.first.first);
    int64_t val2 = y.first.first * y.first.first * x.first.second * sign(y.first.first);
    return (val1 == val2);
}

bool CmpForWords(const std::pair<std::pair<int64_t, int64_t>, size_t>& x,
                 const std::pair<std::pair<int64_t, int64_t>, size_t>& y) {
    return (ValGreater(x, y)) || (ValEqual(x, y) && (x.second < y.second));
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::pair<std::pair<int64_t, int64_t>, size_t>> values(words.size());
    for (size_t i = 0; i < values.size(); ++i) {
        values[i] = {{ScalarProduct(vectors[0], vectors[i]), ScalarProduct(vectors[i], vectors[i])}, i};
    }
    sort(values.begin(), values.end(), CmpForWords);
    std::vector<std::string> answer;
    for (size_t i = 1; i < words.size(); ++i) {
        answer.push_back(words[values[i].second]);
        if ((i + 1 == words.size()) || (ValGreater(values[i], values[i + 1]))) {
            break;
        }
    }
    return answer;
}
