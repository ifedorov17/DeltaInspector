#ifndef GENERALDAO_H
#define GENERALDAO_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDriver>
#include <QtSql>
#include "lesson.h"
#include "student.h"
#include "visitings.h"

class GeneralDAO: public QObject
{
public:
    static GeneralDAO &getInstance();
    static GeneralDAO *getPtr();
    Student *getStudentByStudnum(QString studnum);
    Lesson *getLessonByGroupAndTime(QString group, QString time);
    void doSetVisit(QString studNum, int lessonId);

    int validateLoginPass(const QString& login, const QString& pass);   //Added


    QSqlQueryModel* getGroupsByLogin(const QString& login);       //Added

    int getLessonIdByPK(const QString& group, const QString& time); //Added


    bool addStudent(const Student& student);                     //Added


    bool addGroup(const QString& groupId);                        //Added


    bool addLesson(const Lesson& lesson);                         //Added


    bool addSubject(const QString& subjectName);                  //Added


    QSqlQueryModel* getAllTeacherLogins();                  //Added

    QSqlQueryModel* getAllGroupIds();                       //Added

    QSqlQueryModel* getVisitingsByGroupSubj(const QString& group,
                                            const QString& time);

    QSqlQueryModel* getTimesByLoginGroup(const QString& group,    // Added
                                         const QString& login);
    QSqlQueryModel* getAllSubjects();

    QSqlQueryModel *getAllStudents();

    QSqlQueryModel* getAllLessons();

    QSqlError removeSubject(const QString& p_sbj);

    QSqlError removeStudent(const QString& p_st);

    QSqlError removeLesson(int p_id);

    QSqlError removeGroup(const QString& p_gr);

protected:
    GeneralDAO();

private:
    QSqlDatabase db;

signals:


};

#endif // GENERALDAO_H
