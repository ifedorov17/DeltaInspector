#include "lesson.h"

Lesson::Lesson()
{

}

QString *Lesson::getName()
{
    return naming;
}

QString *Lesson::getLessonTime()
{
    return lessonTime;
}

QString *Lesson::getGroup()
{
    return group;
}

int Lesson::getId()
{
    return id;
}

int Lesson::getAmount()
{
    return amount;
}

QString *Lesson::getTeacher()
{
    return teacher;
}

void Lesson::setName(QString *pName)
{
    naming = pName;
}

void Lesson::setLessonTime(QString *pLessonTime)
{
    lessonTime = pLessonTime;
}

void Lesson::setGroup(QString *pGroup)
{
    group = pGroup;
}

void Lesson::setId(int pId)
{
    id = pId;
}

void Lesson::setAmount(int pAmount)
{
    amount = pAmount;
}

void Lesson::setTeacher(QString *pTeacher)
{
    teacher = pTeacher;
}
