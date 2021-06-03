#ifndef LESSON_H
#define LESSON_H
#include <QString>

class Lesson
{
public:
    Lesson();
    QString getName() const;
    QString getLessonTime() const;
    QString getGroup() const;
    int getId() const;
    int getAmount() const;
    QString getTeacher() const;
    void setName(const QString &pName);
    void setLessonTime(const QString &pLessonTime);
    void setGroup(const QString &pGroup);
    void setId(int pId);
    void setAmount(int pAmount);
    void setTeacher(const QString &pTeacher);
private:
    QString naming;
    QString lessonTime;
    QString group;
    int id;
    int amount; // количество занятий в семестре
    QString teacher;
};

#endif // LESSON_H
