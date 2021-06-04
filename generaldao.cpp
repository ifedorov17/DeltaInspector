#include "generaldao.h"
#include <QDate>
#include<QDebug>


GeneralDAO &GeneralDAO::getInstance()
{
    static GeneralDAO instance;
    return instance;
}

GeneralDAO *GeneralDAO::getPtr()
{
    static GeneralDAO instance;
    return &instance;
}

Student *GeneralDAO::getStudentByStudnum(QString studnum)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    Student* student = new Student();

    student->setStudNum(studnum);

    queryModel->setQuery("SELECT * FROM DI_STUDENTS WHERE (stud_num='" + studnum + "');");

    QString* gruppa = new QString(queryModel->index(0,2).data().toString());
    student->setGroup(*gruppa);
    QString* name = new QString(queryModel->index(0,1).data().toString());
    student->setName(*name);

    return student;
}

Lesson *GeneralDAO::getLessonByGroupAndTime(QString group, QString time)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    Lesson* lesson = new Lesson();
    queryModel->setQuery("SELECT * FROM DI_LESSONS WHERE (gruppa = '" + group +"' AND lesson_time='" + time + "');");
    QString* naming = new QString(queryModel->index(0,0).data().toString());
    lesson->setName(*naming);
    QString* lessonTime = new QString(queryModel->index(0,1).data().toString());
    lesson->setLessonTime(*lessonTime);
    lesson->setGroup(group);
    lesson->setId(queryModel->index(0,3).data().toInt());
    lesson->setAmount(queryModel->index(0,4).data().toInt());

    QString teacherLogin = queryModel->index(0,5).data().toString();
    queryModel->setQuery("SELECT * FROM DI_USERS WHERE login='" + teacherLogin +"';");

    QString* teacherName = new QString(queryModel->index(0,3).data().toString());
    lesson->setTeacher(*teacherName);

    return lesson;
}

void GeneralDAO::doSetVisit(QString studNum, int lessonId)
{
    QDate currentDate = QDate::currentDate();

    QString query = "INSERT INTO di_visitings VALUES ("
        + QString::number(lessonId) + ","
        + "'" + studNum + "',"
        + "'" + currentDate.toString("yyyy-MM-dd") + "');";
    QSqlQueryModel* queryModel = new QSqlQueryModel;
    queryModel->setQuery(query);
    qDebug() << query;
}

int GeneralDAO::validateLoginPass(const QString &login, const QString &pass)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT is_admin FROM di_users WHERE login = '"+ login +"' AND password = '"+pass+"';");
    /*model->lastError().type() != QSqlError::NoError*/
    qDebug() << queryModel->rowCount();
    if(queryModel != nullptr && queryModel->lastError().type() == QSqlError::NoError && queryModel->rowCount() != 0)
    {
        QString* what_kind_of_user = new QString(queryModel->index(0,0).data().toString());
        if(*what_kind_of_user == "true")
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
}

QSqlQueryModel *GeneralDAO::getGroupsByLogin(const QString &login)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT gruppa FROM di_lessons WHERE teacher = '"+ login +"';");
    return  queryModel;
}

int GeneralDAO::getLessonIdByPK(const QString &group, const QString &time)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;


    queryModel->setQuery("SELECT id FROM di_lessons WHERE gruppa = '"+ group +"' AND lesson_time = '"+time+"';");
    if(queryModel != nullptr)
    {
    QString* lesson_id = new QString(queryModel->index(0,0).data().toString());
    return lesson_id->toInt();
    }
    else
    {
        return -1;
    }
}

bool GeneralDAO::addStudent(const Student &student)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;


    queryModel->setQuery("INSERT INTO di_students VALUES ('"+student.getStudNum()+"','"+student.getName()+"','"+student.getGroup()+"');");
    if(queryModel->lastError().type() != QSqlError::NoError)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GeneralDAO::addGroup(const QString &groupId)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;


    queryModel->setQuery("INSERT INTO di_grupps VALUES ('"+groupId+"');");
    if(queryModel->lastError().type() != QSqlError::NoError)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GeneralDAO::addLesson(const Lesson &lesson)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("INSERT INTO di_lessons(naming, lesson_time, gruppa, number, teacher) VALUES ('"
                        +lesson.getName()
                        +"','"
                        +lesson.getLessonTime()
                        +"','"
                        +lesson.getGroup()
                        +"','"
                        +QString::number(lesson.getAmount())
                        +"','"
                        +lesson.getTeacher()+"');"
);

    if(queryModel->lastError().type() != QSqlError::NoError)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GeneralDAO::addSubject(const QString &subjectName)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("INSERT INTO di_subject VALUES ('"+subjectName+"');");
    if(queryModel->lastError().type() != QSqlError::NoError)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QSqlQueryModel *GeneralDAO::getAllTeacherLogins()
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT login FROM di_users WHERE is_admin = 'false';");
    return  queryModel;
}

QSqlQueryModel *GeneralDAO::getAllGroupIds()
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT grupp_num FROM di_grupps;");
    return  queryModel;
}

QSqlQueryModel *GeneralDAO::getVisitingsByGroupTime(const QString &group, const QString &time)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT lesson_id, student_id, visit_time FROM  di_lessons INNER JOIN di_visitings  ON di_lessons.id = di_visitings.lesson_id  WHERE gruppa = '"+group+"' AND lesson_time = '"+time+"';");
    return queryModel;
}

QSqlQueryModel *GeneralDAO::getTimesByLoginGroup(const QString &group, const QString &login)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT lesson_time FROM di_lessons WHERE gruppa = '"+ group +"' AND teacher ='"+login+"';");
    return  queryModel;
}

QSqlQueryModel *GeneralDAO::getAllSubjects()
{
    QSqlQueryModel* queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT * FROM di_subject;");
    return  queryModel;
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

    if (!db.open()) qDebug() << "FUCCC";
    else qDebug() << "xaxa lesi4ka";


}








