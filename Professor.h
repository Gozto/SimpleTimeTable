#ifndef FMFI_ROZVRH___PROJEKT_PROFESSOR_H
#define FMFI_ROZVRH___PROJEKT_PROFESSOR_H
#include <sstream>
#include <string>
#include <vector>


class Professor {

private:
    std::string name = "";
    std::string department = "";
    std::string email = "";
    std::string officeHours = "";

public:
    Professor() {};
    Professor(const std::string &name, const std::string &department, const std::string &email);

    bool setOfficeHours(const std::string &hours); //v tvare: hh:mm-hh:mm
    bool setName(const std::string &name);
    bool setDepartment(const std::string &department);
    bool setEmail(const std::string &email);

    std::string getName() const { return name; }
    std::string getDepartment() const { return department; }
    std::string getEmail() const { return email; }
    std::string getOfficeHours() const { return officeHours; }

    static bool validateName(const std::string &str);
    static bool onlyLetters(const std::string &str);
    static bool validateEmail(const std::string &email);
    static bool validateOfficeHours(const std::string &hours);
};


#endif //FMFI_ROZVRH___PROJEKT_PROFESSOR_H
