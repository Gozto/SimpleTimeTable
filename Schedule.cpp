#include "Schedule.h"


Schedule::Schedule(std::vector<Subject> &subjects)
{
    for (auto s : subjects)
    {
        addSubjectToSchedule(s);
    }
}

bool Schedule::addSubjectToSchedule(const Subject &subject)
{
    if (findSubjectInSchedule(subject))
    {
        return false;
    }
    auto subShared = std::make_shared<Subject>(subject);
    subjects.push_back(subShared);
    return true;
}

bool Schedule::findSubjectInSchedule(const Subject &sub) const
{
    for (const auto &item : subjects)
    {
        if (item->getSubjectCode() == sub.getSubjectCode())
        {
            return true;
        }
    }
    return false;
}

int Schedule::findSubjectIndexInSchedule(const Subject &sub) const
{
    int i = 0;
    for (const auto &item : subjects)
    {
        if (item->getSubjectCode() == sub.getSubjectCode())
        {
            return i;
        }
        i++;
    }
    return -1;
}

bool Schedule::removeSubjectFromSchedule(const Subject &subject)
{
    int index = findSubjectIndexInSchedule(subject);
    if (index == -1)
    {
        return false;
    }
    auto toErase = subjects.begin() + index;
    subjects.erase(toErase);
    return true;
}

int Schedule::findSubjectIndexInScheduleByCode(const std::string &subjectCode) const
{
    int i = 0;
    for (const auto &item : subjects)
    {
        if (item->getSubjectCode() == subjectCode)
        {
            return i;
        }
        i++;
    }
    return -1;
}

bool Schedule::removeSubjectFromScheduleByCode(const std::string &subjectCode)
{
    int index = findSubjectIndexInScheduleByCode(subjectCode);
    if (index == -1)
    {
        return false;
    }
    auto toErase = subjects.begin() + index;
    subjects.erase(toErase);
    return true;
}

std::string &Schedule::printSchedule() const
{
    int i = 0;
    schedulePrinted.clear();
    std::ostringstream oss;
    for (auto s : subjects)
    {
        if (i > 0)
        {
            oss << " || ";
        }
        auto subSched = s->getSubjectSchedule();
        oss << s->getSubjectName();
        if (!subSched.empty())
        {
            oss << " - " << s->getSubjectSchedule();
        }
        else
        {
            oss << " - No time schedule";
        }
        i++;
    }
    schedulePrinted = oss.str();
    return schedulePrinted;
}