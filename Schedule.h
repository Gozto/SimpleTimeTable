#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <map>
#include <string>
#include "Subject.h"


class Schedule {
private:
    std::vector<std::shared_ptr<Subject>> subjects;
    mutable std::string schedulePrinted;

public:

    Schedule() = default;
    Schedule(std::vector<Subject> &subjects);

    bool addSubjectToSchedule(const Subject &subject);
    bool removeSubjectFromScheduleByCode(const std::string &subjectCode);
    bool removeSubjectFromSchedule(const Subject &subject);
    std::string &printSchedule() const;

    bool findSubjectInSchedule(const Subject &sub) const;
    int findSubjectIndexInSchedule(const Subject &sub) const;
    int findSubjectIndexInScheduleByCode(const std::string &subjectCode) const;
    int getNumberOfSubjects() const { return subjects.size(); }
};




#endif // SCHEDULE_H