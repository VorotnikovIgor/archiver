#include "sort_students.h"
#include <tuple>

bool equal_by_date(const Date& date1, const Date& date2) {
    return std::tie(date1.day, date1.month, date1.year) ==
           std::tie(date2.day, date2.month, date2.year);
}

bool first_by_date(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) <
           std::tie(date2.year, date2.month, date2.day);
}

bool equal_by_name(const Student& student1, const Student& student2) {
    return (std::tie(student1.name, student1.last_name) ==
            std::tie(student2.name, student2.last_name));
}

bool first_by_name(const Student& student1, const Student& student2) {
    return (std::tie(student1.last_name, student1.name) <
            std::tie(student2.last_name, student2.name));
}

bool cmp_date(const Student& student1, const Student& student2) {
    if (equal_by_date(student1.birth_date, student2.birth_date)) {
        if (equal_by_name(student1, student2)) {
            return true;
        }
        return first_by_name(student1, student2);
    } else {
        return first_by_date(student1.birth_date, student2.birth_date);
    }
}

bool cmp_name(const Student& student1, const Student& student2) {
    if (equal_by_name(student1, student2)) {
        if (equal_by_date(student1.birth_date, student2.birth_date)) {
            return true;
        }
        return first_by_date(student1.birth_date, student2.birth_date);
    } else {
        return first_by_name(student1, student2);
    }
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        sort(students.begin(), students.end(), cmp_date);
    } else {
        sort(students.begin(), students.end(), cmp_name);
    }
}
