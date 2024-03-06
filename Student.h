#ifndef STUDENT_H
#define STUDENT_H

#include "fstream"
#include <string>
#include <vector>
#include "Schedule.h"

class Student {

private:
    std::string name;
    std::string studentID;
    std::vector<std::shared_ptr<Subject>> enrolledSubjects;
    Schedule studentSchedule;

public:
    Student() = default;
    Student(const std::string& name, const std::string& studentID);
    Student(const std::string& name, const std::string& studentID, const Schedule &schedule);

    bool enrollSubject(const Subject &subject);
    bool enrollSubjectsFromFile(const std::string &fileName);
    /*
     NazovPredmetu;KodPredmetu;PocetKreditov
     Mathematics;MATH101;5
     Physics;PHYS101;4
     */
    bool dropSubjectByCode(const std::string &subjectCode);
    bool dropSubject(const Subject &subject);

    Schedule getSchedule() const { return studentSchedule; }
    std::vector<std::shared_ptr<Subject>> getEnrolledSubjects() { return enrolledSubjects; }
    std::string getPrintedSchedule() const { return studentSchedule.printSchedule(); }
    std::string getName() const { return name; }
    std::string getStudentID() const { return studentID; }
    std::string getEnrolledSubjectsString() const;
    std::string getStudentInfo() const;

    bool writeStudentInfoToFile(const std::string& filename) const;
    int findSubjectIndexInEnrolled(const Subject &subject) const;
    int findSubjectIndexInEnrolledByCode(const std::string &subjectCode) const;
};

#endif // STUDENT_H