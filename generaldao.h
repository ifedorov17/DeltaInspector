#ifndef GENERALDAO_H
#define GENERALDAO_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "lesson.h"
#include "student.h"
#include "visitings.h"

class GeneralDAO: public QObject
{
public:
    static GeneralDAO &getInstance();
    Student *getStudentByStudnum(QString studnum);
    Lesson* getLessonByGroupAndTime(QString group, QString time);
    void doSetVisit(QString studNum, int lessonId);

protected:
    GeneralDAO();

private:
    QSqlDatabase db;
    QSqlQueryModel* queryModel;
};

#endif // GENERALDAO_H
