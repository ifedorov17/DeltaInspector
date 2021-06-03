#include "student.h"

Student::Student()
{

}

QString Student::getStudNum() const
{
    return studNum;
}

QString Student::getName() const
{
    return name;
}

QString Student::getGroup() const
{
    return group;
}

void Student::setStudNum(const QString &pStudNum)
{
    studNum = pStudNum;
}

void Student::setName(const QString &pName)
{
    name = pName;
}

void Student::setGroup(const QString &pGroup)
{
    group = pGroup;
}
