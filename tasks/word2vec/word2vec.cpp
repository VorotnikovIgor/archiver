#include <limits>
#include "word2vec.h"

int64_t ScalarProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return sum;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<int64_t> values(words.size());
    int64_t max_scalar_product = std::numeric_limits<int64_t>::min();
    for (size_t i = 1; i < values.size(); ++i) {
        values[i] = ScalarProduct(vectors[0], vectors[i]);
        max_scalar_product = std::max(max_scalar_product, values[i]);
    }
    std::vector<std::string> answer;
    for (size_t i = 1; i < words.size(); ++i) {
        if (values[i] == max_scalar_product) {
            answer.push_back(words[i]);
        }
    }
    return answer;
}
