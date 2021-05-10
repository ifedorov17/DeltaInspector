#ifndef STUDENT_H
#define STUDENT_H
#include "baseentity.h"

class Student: public BaseEntity
{

public:
    Student();

private:
    QString *stud_num;
    QString *name;
    QString *group;
};

#endif // STUDENT_H
