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

    int validateLoginPass(const QString& login, const QString& pass);   //Validates login and password
                                                            //Returns -1 if login does not exist or password is incorrect
                                                            //Returns 0 if login and password are correct and it is a regular user
                                                            //Returns 1 if login and password are correct and it is an admin

    QSqlQueryModel* getGroupsByLogin(const QString& login);       //Returns QSqlQueryModel* of GROUPS, associated with argument login

    int getLessonIdByPK(const QString& group, const QString& time); //Returns ID of LESSON by PK

    bool addVisiting(const Visitings& visit);                     //ADDS a VISITING into the database by argument Visiting
                                                            //Returns true if successfully, false otherwise

    bool addStudent(const Student& student);                      //ADDS a STUDENT into the database by argument Student
                                                            //Returns true if successfully, false otherwise

    bool addGroup(const QString& groupId);                        //ADDS a GROUP into the database by argument QString& groupId
                                                            //Returns true if successfully, false otherwise

    bool addLesson(const Lesson& lesson);                         //Adds a  into the database by argument Lesson
                                                            //Returns true if successfully, false otherwise

    bool addSubject(const QString& subjectName);                  //ADDS a SUBJECT into the database by argument QString& subjectName
                                                            //Returns true if successfully, false otherwise

    QSqlQueryModel* getAllTeacherLogins();                  //Returns ALL teacher LOGINS e.g. the ones, which are NOT stated as ADMINS

    QSqlQueryModel* getAllGroupIds();                       //Returns ALL GROUP ids

    QSqlQueryModel* getVisitingsByGroupTime(const QString& group, //Returns VISITINGS by GROUP and TIME
                                            const QString& time);

    QSqlQueryModel* getTimesByLoginGroup(const QString& group,    //Returns TIMES for arguments which are LOGIN and GROUP
                                         const QString& login);

protected:
    GeneralDAO();

private:
    QSqlDatabase db;
    QSqlQueryModel* queryModel;
};

#endif // GENERALDAO_H
