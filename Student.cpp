#include "Student.h"

Student::Student(const std::string &name, const std::string &studentID)
{
    if (Professor::validateName(name))
    {
        this->name = name;
    }
    if (Subject::onlyLettersAndDigits(studentID))
    {
        this->studentID = studentID;
    }
}

Student::Student(const std::string& name, const std::string& studentID, const Schedule &schedule)
: studentSchedule(schedule)
{
    if (Professor::validateName(name))
    {
        this->name = name;
    }
    if (Subject::onlyLettersAndDigits(studentID))
    {
        this->studentID = studentID;
    }
}

bool Student::enrollSubject(const Subject &subject)
{

    if (!studentSchedule.addSubjectToSchedule(subject))
    {
        return false;
    }
    auto subjectPtr = std::make_shared<Subject>(subject);
    enrolledSubjects.push_back(subjectPtr);
    return true;
}

bool Student::dropSubject(const Subject &subject)
{
    int index = findSubjectIndexInEnrolled(subject);
    if (index == -1)
    {
        return false;
    }
    auto toErase = enrolledSubjects.begin() + index;
    enrolledSubjects.erase(toErase);
    studentSchedule.removeSubjectFromSchedule(subject);
    return true;
}


int Student::findSubjectIndexInEnrolled(const Subject &subject) const
{
    int i = 0;
    for (auto s : enrolledSubjects)
    {
        if (s->getSubjectCode() == subject.getSubjectCode())
        {
            return i;
        }
        i++;
    }
    return -1;
}

int Student::findSubjectIndexInEnrolledByCode(const std::string &subjectCode) const
{
    int i = 0;
    for (auto s : enrolledSubjects)
    {
        if (s->getSubjectCode() == subjectCode)
        {
            return i;
        }
        i++;
    }
    return -1;
}

bool Student::dropSubjectByCode(const std::string &subjectCode)
{
    int index = findSubjectIndexInEnrolledByCode(subjectCode);
    if (index == -1)
    {
        return false;
    }
    auto toErase = enrolledSubjects.begin() + index;
    enrolledSubjects.erase(toErase);
    studentSchedule.removeSubjectFromScheduleByCode(subjectCode);
    return true;
}

std::string Student::getStudentInfo() const
{
    std::ostringstream oss;
    oss << "Name: ";
    if (name.empty())
    {
        oss << "no info\n";
    }
    else
    {
        oss << name << '\n';
    }
    oss << "studentID: ";
    if (studentID.empty())
    {
        oss << "no info\n";
    }
    else
    {
        oss << studentID << '\n';
    }
    oss << "Enrolled subjects: " << getEnrolledSubjectsString() << '\n';
    oss << "Student schedule: " << studentSchedule.printSchedule();
    return oss.str();
}

std::string Student::getEnrolledSubjectsString() const
{
    std::ostringstream res;
    int i = 0;
    for (auto s : enrolledSubjects)
    {
        if (i > 0)
        {
            res << ", ";
        }
        res << s->getSubjectName();
        i++;
    }
    return res.str();
}

bool Student::writeStudentInfoToFile(const std::string &filename) const
{
    std::ofstream fileOut(filename);
    if (fileOut.is_open())
    {
        fileOut << getStudentInfo();
        fileOut.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::enrollSubjectsFromFile(const std::string &fileName)
{
    std::ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        return false;
    }
    std::string line;
    while (getline(fileIn, line))
    {
        std::istringstream iss(line);
        std::string subjectName, subjectCode, creditStr;
        if (std::getline(iss, subjectName, ';') &&
            std::getline(iss, subjectCode, ';') &&
            std::getline(iss, creditStr))
        {
            int credits = std::stoi(creditStr);
            Subject subject(subjectName, subjectCode, credits);
            enrollSubject(subject);
        }
    }
    fileIn.close();
    return true;
}
