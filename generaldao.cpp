#include "generaldao.h"

GeneralDAO *GeneralDAO::getInstance()
{
    if (GeneralDAO::instance == nullptr) {
        instance = new GeneralDAO();
    }
    return instance;
}

Student *GeneralDAO::getStudentByStudnum(QString studnum)
{
    Student* student = new Student();

    //////
    return student;
}

Lesson *GeneralDAO::getLessonByGroupAndTime(QString group, QString time)
{
    Lesson* lesson = new Lesson();

    //////
    return lesson;
}

void GeneralDAO::doSetVisit(QString studNum, int lessonId)
{
    //запись в таблицу visitings
}

GeneralDAO::GeneralDAO()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("195.19.32.74");
    db.setDatabaseName("fn1132_2020");
    db.setPort(5432);
    db.setUserName("student");
    db.setPassword("bmstu");
    db.open();

    queryModel = new QSqlQueryModel(this);
}
