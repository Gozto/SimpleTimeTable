#include "Professor.h"

Professor::Professor(const std::string &name, const std::string &department, const std::string &email)
{
    if (validateName(name))
    {
        this->name = name;
    }
    if (onlyLetters(department))
    {
        this->department = department;
    }
    if (validateEmail(email))
    {
        this->email = email;
    }
}

bool Professor::validateName(const std::string &str)
{
    for (char ch : str)
    {
        if (!std::isalpha(ch) && ch != ' ' && ch != '.')
        {
            return false;
        }
    }
    return true;
}

bool Professor::onlyLetters(const std::string &str)
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

bool Professor::validateEmail(const std::string &email)
{
    int num = 0;
    for (char ch : email)
    {
        if (!std::isalnum(ch) && ch != '@' && ch != '.')
        {
            return false;
        }
        if (ch == '@')
        {
            if (num == 0)
            {
                num++;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool Professor::setName(const std::string &name)
{
    if (validateName(name))
    {
        this->name = name;
        return true;
    }
    return false;
}

bool Professor::setEmail(const std::string &email)
{
    if (validateEmail(email))
    {
        this->email = email;
        return true;
    }
    return false;
}

bool Professor::setDepartment(const std::string &department)
{
    if (onlyLetters(department))
    {
        this->department = department;
        return true;
    }
    return false;
}

bool Professor::validateOfficeHours(const std::string &hours)
{
    int h1, m1, h2, m2;
    char del1, del2, delMid;
    std::istringstream iss(hours);
    iss >> h1 >> del1 >> m1 >> delMid >> h2 >> del2 >> m2;
    if (h1 < 6 || h1 > 21 || m1 > 59 || m1 < 0 || h2 < 6 || h2 > 21 || m2 > 59 || m2 < 0 || h1 > h2 || delMid != '-'
    || del1 != ':' || del2 != ':')
    {
        return false;
    }
    return true;
}

bool Professor::setOfficeHours(const std::string &hours)
{
    if (validateOfficeHours(hours))
    {
        officeHours = hours;
        return true;
    }
    return false;
}
