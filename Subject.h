#ifndef FMFI_ROZVRH___PROJEKT_SUBJECT_H
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>
#include "Professor.h"
#include "unordered_map"
#include "memory"


enum class WeekDay {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};



class Subject
{
private:
    std::vector<std::shared_ptr<Professor>> professors;
    std::string subjectName = "";
    std::string subjectCode = "";
    int numberOfCredits = -1;
    std::string description = "";
    std::vector<std::pair<WeekDay, std::string>> schedule;
    mutable std::string subjectScheduleString;
    mutable std::string subjectInfoString;
    mutable std::string subjectProfesorsString;

public:
    Subject() {};
    Subject(const std::string &name, const std::string &code, const int &credits);
    Subject(const std::string &name, const std::string &code, const int &credits, const std::string &desc, const Professor &prof);
    Subject(const std::string &name, const std::string &code, const int &credits, const std::string &desc, const Professor &prof, const std::pair<WeekDay, std::string> &sched); //schedule je v tvare pon_16:30; uto_12:30


    std::string &getAllProfessors() const;
    std::string getSubjectName() const {return subjectName;}
    std::string getSubjectCode() const {return subjectCode;}
    int getSubjectNumOfCredits() const {return numberOfCredits;}
    std::string  getSubjectDescription() const {return description;}
    std::string getSubjectSchedule() const;
    std::string &getSubjectInfo() const;
    std::vector<std::pair<WeekDay, std::string>> getSubjectSchedulePairs() const { return schedule; };

    bool addProfessor(const Professor &prof);
    bool setSubjectName(const std::string &subName);
    bool setSubjectCode(const std::string &subCode);
    bool setSubjectCredits(const int &cred);
    bool setSubjectDescription(const std::string &desc);
    bool addSubjectSchedule(const std::string &time, const WeekDay day);

    static bool onlyLettersAndDigits(const std::string &str);
    static bool onlyLetters(const std::string &str);
    static bool validateScheduleTime(const std::string &time);
    static std::string weekDayToString(const WeekDay &day);
    bool isScheduleNew(const std::pair<WeekDay, std::string> &newSched) const;
};


#endif //FMFI_ROZVRH___PROJEKT_SUBJECT_H
