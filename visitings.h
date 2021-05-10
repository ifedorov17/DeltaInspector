#ifndef VISITINGS_H
#define VISITINGS_H
#include <QString>

class Visitings
{
public:
    Visitings();
    int getLessonId();
    QString getStudentId();
    QString getVisitTime();
    void setLessonId(int pId);
    void setStudentId(QString &pStudentId);
    void setVisitTime(QString &pVisitTime);

private:
    int lessonId;
    QString studentId; // номер студака ссылается на Students.STUD_NUM
    QString visitTime; // дата посещения занятия
};

#endif // VISITINGS_H
