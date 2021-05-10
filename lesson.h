#ifndef LESSON_H
#define LESSON_H
#include <QString>

class Lesson
{
public:
    Lesson();
private:
    QString naming[100];
    QString leeson_time[10];
    QString group[10];
    int id;
    int amount; // количество занятий в семестре
    QString teacher[50];
};

#endif // LESSON_H
