#include "Subject.h"

Subject::Subject(const std::string &name, const std::string &code, const int &credits)
{
    setSubjectName(name);
    setSubjectCode(code);
    setSubjectCredits(credits);
}

Subject::Subject(const std::string &name, const std::string &code, const int &credits,
                 const std::string &desc, const Professor &prof)
{
    setSubjectName(name);
    setSubjectCode(code);
    setSubjectCredits(credits);
    setSubjectDescription(desc);
    addProfessor(prof);
}

Subject::Subject(const std::string &name, const std::string &code, const int &credits, const std::string &desc,
                 const Professor &prof, const std::pair<WeekDay, std::string> &sched)
                 {
     setSubjectName(name);
     setSubjectCode(code);
     setSubjectCredits(credits);
     setSubjectDescription(desc);
     addProfessor(prof);
     WeekDay day = sched.first;
     std::string time = sched.second;
     if (validateScheduleTime(time))
     {
         addSubjectSchedule(time, day);
     }
                 }

std::string &Subject::getAllProfessors() const
{
    subjectProfesorsString.clear();
    int i = 0;
    for (const auto &p : professors)
    {
        if (i > 0)
        {
            subjectProfesorsString += "; ";
        }
        subjectProfesorsString += p->getName();
        i++;
    }
    return subjectProfesorsString;
}

std::string Subject::getSubjectSchedule() const
{
    std::string result;
    int i = 0;
    for (auto s : schedule)
    {
        if (i > 0) {
            result += "; ";
        }
        result += weekDayToString(s.first);
        result += '_';
        result += s.second;

        i++;
    }
    return result;
}

bool Subject::setSubjectName(const std::string &subName)
{
    if (!subName.empty())
    {
        if (!onlyLetters(subName))
        {
            return false;
        }
        subjectName = subName;
        return true;
    }
    return false;
}

bool Subject::onlyLettersAndDigits(const std::string &str) {
    for (char ch : str)
    {
        if (!std::isalpha(ch) && !std::isdigit(ch) && ch != ' ')
        {
            return false;
        }
    }
    return true;
}

bool Subject::onlyLetters(const std::string &str)
{
    for (char ch : str)
    {
        if (!std::isalpha(ch) && ch != ' ')
        {
            return false;
        }
    }
    return true;
}

bool Subject::setSubjectCode(const std::string &subCode)
{
    if (!subCode.empty())
    {
        if (!onlyLettersAndDigits(subCode))
        {
            return false;
        }
        subjectCode = subCode;
        return true;
    }
    return false;
}

bool Subject::setSubjectCredits(const int &cred)
{
    if (cred >= 0)
    {
        numberOfCredits = cred;
        return true;
    }
    return false;
}

bool Subject::setSubjectDescription(const std::string &desc)
{
    if (!desc.empty())
    {
        if (onlyLettersAndDigits(desc))
        {
            description = desc;
            return true;
        }
    }
    return false;
}

bool Subject::addSubjectSchedule(const std::string &time, const WeekDay day)
{
    if (validateScheduleTime(time) && isScheduleNew(std::make_pair(day, time)))
    {
        schedule.emplace_back(day, time);
        return true;
    }
    return false;
}

std::string &Subject::getSubjectInfo() const
{
    std::ostringstream infoStream;
    infoStream << "Name: " << getSubjectName() << '\n'
               << "Professor(s): " << getAllProfessors() << '\n'
               << "Subject code: " << getSubjectCode() << '\n'
               << "Decription: " << getSubjectDescription() << '\n'
               << "Number of credits: " << getSubjectNumOfCredits() << '\n'
               << "Schedule: " << getSubjectSchedule();

    subjectInfoString = infoStream.str();
    return subjectInfoString;
}

bool Subject::validateScheduleTime(const std::string &time)
{
    std::istringstream iss(time);
    int hod;
    int min;
    char del;
    iss >> hod >> del >> min;
    if (hod > 20 || hod < 7)
    {
        return false;
    }
    if (min > 59 || min < 00)
    {
        return false;
    }
    return true;
}

bool Subject::addProfessor(const Professor &prof)
{
    auto profShared = std::make_shared<Professor>(prof);
    for (const auto &p : professors)
    {
        if (p->getName() == profShared->getName())
        {
            return false;
        }
    }
    professors.push_back(profShared);
    return true;
}


std::string Subject::weekDayToString(const WeekDay &day) {
    switch (day) {
        case WeekDay::Monday:    return "Monday";
        case WeekDay::Tuesday:   return "Tuesday";
        case WeekDay::Wednesday: return "Wednesday";
        case WeekDay::Thursday:  return "Thursday";
        case WeekDay::Friday:    return "Friday";
        case WeekDay::Saturday:  return "Saturday";
        case WeekDay::Sunday:    return "Sunday";
        default:                 return "Unknown";
    }
};

bool Subject::isScheduleNew(const std::pair<WeekDay, std::string>& newSched) const
{
    for (const auto &e : schedule)
    {
        if (e == newSched) {
            return false;
        }
    }
    return true;
}




