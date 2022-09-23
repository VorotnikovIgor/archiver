#include "admission.h"
#include <tuple>
#include <iostream>

bool CmpForApplicants(const Applicant* applicant1, const Applicant* applicant2) {
    return std::tie(applicant2->points, applicant1->student.birth_date.year, applicant1->student.birth_date.month,
                    applicant1->student.birth_date.day, applicant1->student.name) <
           std::tie(applicant1->points, applicant2->student.birth_date.year, applicant2->student.birth_date.month,
                    applicant2->student.birth_date.day, applicant2->student.name);
}

bool CmpForStudents(const Student* student1, const Student* student2){
    return std::tie(student1->name, student1->birth_date.year, student1->birth_date.month, student1->birth_date.day) <
           std::tie(student2->name, student2->birth_date.year, student2->birth_date.month, student2->birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> sorted_applicants;
    sorted_applicants.reserve(applicants.size());
    for (const auto& applicant: applicants) {
        sorted_applicants.push_back(&applicant);
    }
    sort(sorted_applicants.begin(), sorted_applicants.end(), CmpForApplicants);
    std::unordered_map<std::string, int> num_of_left_places;
    AdmissionTable admission_results;
    for (const auto& university : universities) {
        num_of_left_places[university.name] = university.max_students;
    }
    for (const auto& applicant : sorted_applicants) {
        for (const auto& wished_university : applicant->wish_list) {
            if (num_of_left_places[wished_university]) {
                --num_of_left_places[wished_university];
                admission_results[wished_university].push_back(&applicant->student);
                break;
            }
        }
    }
    for (auto& [university, students] : admission_results) {
        sort(students.begin(), students.end(), CmpForStudents);
    }
    return admission_results;
}
