#ifndef LESSON_H
#define LESSON_H
#include "baseentity.h"

class Lesson : public BaseEntity
{
public:
    Lesson();
private:
    QString *naming;
    QString *lesson_time;
    QString *group;
    int id;
    int amount; // количество занятий в семестре
    QString *teacher;
};

#endif // LESSON_H
