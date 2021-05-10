#include "visitings.h"

Visitings::Visitings()
{

}

int Visitings::getLessonId()
{
    return lessonId;
}

QString Visitings::getStudentId()
{
    return studentId;
}

QString Visitings::getVisitTime()
{
    return visitTime;
}

void Visitings::setLessonId(int pId)
{
    lessonId = pId;
}

void Visitings::setStudentId(QString &pStudentId)
{
    studentId = pStudentId;
}

void Visitings::setVisitTime(QString &pVisitTime)
{
    visitTime = pVisitTime;
}
