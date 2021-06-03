#ifndef VISITINGS_H
#define VISITINGS_H
#include <QString>

class Visitings
{
public:
    Visitings();
    int getLessonId();
    QString getStudentId() const;
    QString getVisitTime() const;
    void setLessonId(int pId);
    void setStudentId(const QString &pStudentId);
    void setVisitTime(const QString &pVisitTime);

private:
    int lessonId;
    QString studentId; // номер студака ссылается на Students.STUD_NUM
    QString visitTime; // дата посещения занятия
};

#endif // VISITINGS_H
