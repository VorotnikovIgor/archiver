#include "scorer.h"

bool Cmp(Event& e1, Event e2) {
    return e1.time < e2.time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events events2 = events;
    sort(events2.begin(), events2.end(), Cmp);
    std::set<std::pair<StudentName, TaskName>> check_success;
    std::set<std::pair<StudentName, TaskName>> open_request;
    for (const auto& ev : events2) {
        std::pair<StudentName, TaskName> students_task = {ev.student_name, ev.task_name};
        if (ev.time > score_time) {
            break;
        }
        if (ev.event_type == EventType::CheckFailed) {
            if (check_success.find(students_task) != check_success.end()) {
                check_success.erase(students_task);
            }
        } else if (ev.event_type == EventType::CheckSuccess) {
            check_success.insert(students_task);
        } else if (ev.event_type == EventType::MergeRequestOpen) {
            open_request.insert(students_task);
        } else {
            if (open_request.find(students_task) != open_request.end()) {
                open_request.erase(students_task);
            }
        }
    }
    ScoreTable answer;
    for (const auto& students_task : check_success) {
        if (open_request.find(students_task) == open_request.end()) {
            answer[students_task.first].insert(students_task.second);
        }
    }
    return answer;
}
