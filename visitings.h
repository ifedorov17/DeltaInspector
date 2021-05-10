#ifndef VISITINGS_H
#define VISITINGS_H
#include <QString>

class Visitings
{
public:
    Visitings();
private:
    int lesson_id;
    QString student_id[10]; // номер студака ссылается на Students.STUD_NUM
    QString visit_time[20]; // дата посещения занятия
};

#endif // VISITINGS_H
