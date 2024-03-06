#include "StudyProgram.h"

StudyProgram::StudyProgram(const std::string &programName, const int &credits, const Schedule &sched)
: totalCredits(credits), programSchedule(sched)
{
    if (Professor::onlyLetters(programName))
    {
        this->programName = programName;
    }
}

StudyProgram::StudyProgram(const std::string &programName, std::vector<std::shared_ptr<Subject>> &subjects,
                           std::vector<std::shared_ptr<Professor>> &profs, const Schedule &sched)
                           : subjects(subjects), professors(profs), programSchedule(sched) {
    if (Professor::onlyLetters(programName))
    {
        this->programName = programName;
    }
    int creds = 0;
    for (const auto &s : subjects)
    {
        creds += s->getSubjectNumOfCredits();
    }
    totalCredits = creds;
}

StudyProgram::StudyProgram(const std::string &programName, std::vector<std::shared_ptr<Subject>> &subjects,
                           std::vector<std::shared_ptr<Professor>> &profs,
                           std::vector<std::shared_ptr<Student>> students, const Schedule &sched)
                           : subjects(subjects), professors(profs), students(students), programSchedule(sched) {
    if (Professor::onlyLetters(programName))
    {
        this->programName = programName;
    }
    int creds = 0;
    for (const auto &s : subjects)
    {
        creds += s->getSubjectNumOfCredits();
    }
    totalCredits = creds;
}

int StudyProgram::findSubjectIndexInProgramByCode(const std::string &subjectCode) const
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

int StudyProgram::findSubjectIndexInProgram(const Subject &subject) const
{
    int i = 0;
    for (const auto &item : subjects)
    {
        if (item->getSubjectCode() == subject.getSubjectCode())
        {
            return i;
        }
        i++;
    }
    return -1;
}

int StudyProgram::findStudentIndexInProgram(const Student &student) const
{
    int i = 0;
    for (const auto &item : students)
    {
        if (item->getStudentID() == student.getStudentID())
        {
            return i;
        }
        i++;
    }
    return -1;
}

int StudyProgram::findStudentIndexInProgramByID(const std::string &studentID) const
{
    int i = 0;
    for (const auto &item : students)
    {
        if (item->getStudentID() == studentID)
        {
            return i;
        }
        i++;
    }
    return -1;
}

bool StudyProgram::addSubject(const Subject &subject)
{
    if (findSubjectIndexInProgram(subject) != -1)
    {
        return false;
    }
    auto subjectPtr = std::make_shared<Subject>(subject);
    subjects.push_back(subjectPtr);
    programSchedule.addSubjectToSchedule(subject);
    return true;
}

bool StudyProgram::removeSubject(const Subject &subject)
{
    int index = findSubjectIndexInProgram(subject);
    if (index == -1)
    {
        return false;
    }
    auto toRemove = subjects.begin() + index;
    subjects.erase(toRemove);
    programSchedule.removeSubjectFromSchedule(subject);
    return true;
}

bool StudyProgram::removeSubjectByCode(const std::string &subjectCode)
{
    int index = findSubjectIndexInProgramByCode(subjectCode);
    if (index == -1)
    {
        return false;
    }
    auto toRemove = subjects.begin() + index;
    subjects.erase(toRemove);
    programSchedule.removeSubjectFromScheduleByCode(subjectCode);
    return true;
}

bool StudyProgram::addStudent(const Student &student)
{
    if (findStudentIndexInProgram(student) != -1)
    {
        return false;
    }
    auto studentPtr = std::make_shared<Student>(student);
    students.push_back(studentPtr);
    return true;
}

bool StudyProgram::removeStudent(const Student &student)
{
    int index = findStudentIndexInProgram(student);
    if (index == -1)
    {
        return false;
    }
    auto toRemove = students.begin() + index;
    students.erase(toRemove);
    return true;
}

bool StudyProgram::removeStudentByID(const std::string &studentCode)
{
    int index = findStudentIndexInProgramByID(studentCode);
    if (index == -1)
    {
        return false;
    }
    auto toRemove = students.begin() + index;
    students.erase(toRemove);
    return true;
}
