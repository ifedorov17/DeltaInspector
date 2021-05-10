#include "student.h"

Student::Student()
{

}

QString Student::getStudNum()
{
    return studNum;
}

QString Student::getName()
{
    return name;
}

QString Student::getGroup()
{
    return group;
}

void Student::setStudNum(QString &pStudNum)
{
    studNum = pStudNum;
}

void Student::setName(QString &pName)
{
    name = pName;
}

void Student::setGroup(QString &pGroup)
{
    group = pGroup;
}
