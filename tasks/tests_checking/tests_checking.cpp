#include "tests_checking.h"
#include <deque>
#include <iostream>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<size_t> cur_order_in_idx;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            cur_order_in_idx.push_front(i);
        } else {
            cur_order_in_idx.push_back(i);
        }
    }
    std::vector<std::string> answer(queries.size());
    for (size_t i = 0; i < queries.size(); ++i) {
        answer[i] = student_actions[cur_order_in_idx[queries[i] - 1]].name;
    }
    return answer;
}
