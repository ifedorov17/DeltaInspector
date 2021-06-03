#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class Student
{

public:
    Student();
    QString getStudNum() const;
    QString getName() const;
    QString getGroup() const;
    void setStudNum(const QString &pStudNum);
    void setName(const QString &pName);
    void setGroup(const QString &pGroup);

private:
    QString studNum;
    QString name;
    QString group;
};

#endif // STUDENT_H
