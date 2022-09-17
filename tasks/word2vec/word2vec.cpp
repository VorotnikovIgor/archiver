#include "word2vec.h"

const double eps = 1e-8;

int scalar_product_in_pow(const std::vector<int>& a, const std::vector<int>& b, int p) {
    int sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    if (p == 2) {
        sum *= sum;
    }
    return sum;
}

double calc_value(const int x, const int y) {
    return static_cast<double>(x) / static_cast<double>(y);
}

bool cmp_for_doubles(const std::pair<double, size_t>& x, const std::pair<double, size_t>& y) {
    return x.first + eps >= y.first;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::pair<double, size_t>> values(words.size());
    for (size_t i = 0; i < values.size(); ++i) {
        values[i] = {
            scalar_product_in_pow(vectors[0], vectors[i], 2) / scalar_product_in_pow(vectors[i], vectors[i], 1), i};
    }
    sort(values.begin(), values.end(), cmp_for_doubles);
    std::vector<std::string> answer;
    for (size_t i = 1; i < words.size(); ++i) {
        answer.push_back(words[values[i].second]);
        if ((i + 1 == words.size()) || (values[i + 1].first + eps < values[i].first)) {
            break;
        }
    }
    return answer;
}
