#include "scorer.h"

struct task_state {
    time_t last_success = 0;
    time_t last_fail = 0;
    int dif_of_requests = 0;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<std::pair<StudentName, TaskName>, task_state> info;
    for (const auto& ev : events) {
        std::pair<StudentName, TaskName> students_task = {ev.student_name, ev.task_name};
        if (ev.time > score_time) {
            continue;
        }
        if (ev.event_type == EventType::CheckFailed) {
            info[students_task].last_fail = std::max(ev.time, info[students_task].last_fail);
        } else if (ev.event_type == EventType::CheckSuccess) {
            info[students_task].last_success = std::max(ev.time, info[students_task].last_success);
        } else if (ev.event_type == EventType::MergeRequestOpen) {
            info[students_task].dif_of_requests += 1;
        } else {
            info[students_task].dif_of_requests -= 1;
        }
    }
    ScoreTable answer;
    for (const auto& [students_task, status] : info) {
        if (status.dif_of_requests == 0 && status.last_success > status.last_fail) {
            answer[students_task.first].insert(students_task.second);
        }
    }
    return answer;
}
