#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class Student
{

public:
    Student();
    QString getStudNum();
    QString getName();
    QString getGroup();
    void setStudNum(QString &pStudNum);
    void setName(QString &pName);
    void setGroup(QString &pGroup);

private:
    QString studNum;
    QString name;
    QString group;
};

#endif // STUDENT_H
