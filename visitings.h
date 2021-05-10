#ifndef VISITINGS_H
#define VISITINGS_H
#include "baseentity.h"

class Visitings : public BaseEntity
{
public:
    Visitings();
private:
    int lesson_id;
    QString *student_id; // номер студака ссылается на Students.STUD_NUM
    QString *visit_time; // дата посещения занятия
};

#endif // VISITINGS_H
