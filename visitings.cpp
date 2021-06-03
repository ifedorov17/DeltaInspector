#include "visitings.h"

Visitings::Visitings()
{

}

int Visitings::getLessonId()
{
    return lessonId;
}

QString Visitings::getStudentId() const
{
    return studentId;
}

QString Visitings::getVisitTime() const
{
    return visitTime;
}

void Visitings::setLessonId(int pId)
{
    lessonId = pId;
}

void Visitings::setStudentId(const QString &pStudentId)
{
    studentId = pStudentId;
}

void Visitings::setVisitTime(const QString &pVisitTime)
{
    visitTime = pVisitTime;
}
