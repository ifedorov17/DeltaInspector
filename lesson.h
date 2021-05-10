#ifndef LESSON_H
#define LESSON_H
#include <QString>

class Lesson
{
public:
    Lesson();
    QString *getName();
    QString *getLessonTime();
    QString *getGroup();
    int getId();
    int getAmount();
    QString *getTeacher();
    void setName(QString *pName);
    void setLessonTime(QString *pLessonTime);
    void setGroup(QString *pGroup);
    void setId(int pId);
    void setAmount(int pAmount);
    void setTeacher(QString *pTeacher);
private:
    QString *naming;
    QString *lessonTime;
    QString *group;
    int id;
    int amount; // количество занятий в семестре
    QString *teacher;
};

#endif // LESSON_H
