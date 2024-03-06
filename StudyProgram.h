#ifndef STUDYPROGRAM_H
#define STUDYPROGRAM_H

#include <string>
#include <vector>
#include "Student.h"

class StudyProgram {
private:
    Schedule programSchedule; // rozvrh vsetkych predmetov
    std::string programName;
    std::vector<std::shared_ptr<Subject>> subjects;
    std::vector<std::shared_ptr<Professor>> professors;
    std::vector<std::shared_ptr<Student>> students; // kazdy student ma vlastny rozvrh pretoze nie vsetci studenti z jedneho programu maju rovnake predmety
    int totalCredits;

public:
    StudyProgram() = default;
    StudyProgram(const std::string &programName, std::vector<std::shared_ptr<Subject>> &subjects,
                 std::vector<std::shared_ptr<Professor>> &profs, const Schedule &sched);
    StudyProgram(const std::string &programName, std::vector<std::shared_ptr<Subject>> &subjects,
                 std::vector<std::shared_ptr<Professor>> &profs, std::vector<std::shared_ptr<Student>> students,
                 const Schedule &sched);
    StudyProgram(const std::string &programName, const int &credits, const Schedule &sched);

    void setSchedule(const Schedule &schedule) { programSchedule = schedule; }
    bool addSubject(const Subject &subject);
    bool removeSubject(const Subject &subject);
    bool removeSubjectByCode(const std::string &subjectCode);
    bool addStudent(const Student &student);
    bool removeStudent(const Student &student);
    bool removeStudentByID(const std::string &studentCode);

    Schedule getProgramSchedule() const { return programSchedule; }
    int getTotalCredits() const { return totalCredits; }
    std::vector<std::shared_ptr<Subject>> getAllSubjects() const { return subjects; }
    std::vector<std::shared_ptr<Professor>> getAllProfessors() const { return professors; }
    std::vector<std::shared_ptr<Student>> getAllStudents() const { return students; }
    std::string getProgramName() const { return programName; }

    int findSubjectIndexInProgramByCode(const std::string &subjectCode) const;
    int findSubjectIndexInProgram(const Subject &subjectCode) const;
    int findStudentIndexInProgram(const Student &student) const;
    int findStudentIndexInProgramByID(const std::string &studentID) const;
};

#endif // STUDYPROGRAM_H