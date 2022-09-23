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
    std::vector<int64_t> values(words.size() - 1);
    int64_t max_scalar_product = std::numeric_limits<int64_t>::min();
    for (size_t i = 0; i < values.size() - 1; ++i) {
        values[i] = ScalarProduct(vectors[0], vectors[i + 1]);
        max_scalar_product = std::max(max_scalar_product, values[i]);
    }
    std::vector<std::string> answer;
    for (size_t i = 0; i < words.size() - 1; ++i) {
        if (values[i] == max_scalar_product) {
            answer.push_back(words[i + 1]);
        }
    }
    return answer;
}
