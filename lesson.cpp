#include "lesson.h"

Lesson::Lesson()
{

}

QString Lesson::getName() const
{
    return naming;
}

QString Lesson::getLessonTime() const
{
    return lessonTime;
}

QString Lesson::getGroup() const
{
    return group;
}

int Lesson::getId() const
{
    return id;
}

int Lesson::getAmount() const
{
    return amount;
}

QString Lesson::getTeacher() const
{
    return teacher;
}

void Lesson::setName(const QString &pName)
{
    naming = pName;
}

void Lesson::setLessonTime(const QString &pLessonTime)
{
    lessonTime = pLessonTime;
}

void Lesson::setGroup(const QString &pGroup)
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

void Lesson::setTeacher(const QString &pTeacher)
{
    teacher = pTeacher;
}
