#include <cmath>
#include "word2vec.h"

const double EPS = 1e-6;

int ScalarProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

double CalcValue(const int x, const int y) {
    return static_cast<double>(x) / sqrt(static_cast<double>(y));
}

bool CmpForDoubles(const std::pair<double, size_t>& x, const std::pair<double, size_t>& y) {
    return (x.first > y.first + EPS) || ((std::abs(x.first - y.first) < EPS) && (x.second < y.second));
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::pair<double, size_t>> values(words.size());
    for (size_t i = 0; i < values.size(); ++i) {
        values[i] = {CalcValue(ScalarProduct(vectors[0], vectors[i]), ScalarProduct(vectors[i], vectors[i])), i};
    }
    sort(values.begin(), values.end(), CmpForDoubles);
    std::vector<std::string> answer;
    for (size_t i = 1; i < words.size(); ++i) {
        answer.push_back(words[values[i].second]);
        if ((i + 1 == words.size()) || (values[i + 1].first + EPS < values[i].first)) {
            break;
        }
    }
    return answer;
}
