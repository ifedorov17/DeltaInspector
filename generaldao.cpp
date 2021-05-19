//#include "generaldao.h"
//#include <QDate>
//#include<QDebug>

//GeneralDAO *GeneralDAO::getInstance()
//{
//    if (GeneralDAO::instance == nullptr) {
//        instance = new GeneralDAO();
//    }
//    return instance;
//}

//Student *GeneralDAO::getStudentByStudnum(QString studnum)
//{
//    Student* student = new Student();

//    student->setStudNum(&studnum);
//    queryModel->setQuery("SELECT * FROM DI_STUDENTS WHERE (stud_num='" + studnum + "');");

//    QString* gruppa = new QString(queryModel->index(0,2).data().toString());
//    student->setGroup(gruppa);
//    QString* name = new QString(queryModel->index(0,1).data().toString());
//    student->setName(name);

//    return student;
//}

//Lesson *GeneralDAO::getLessonByGroupAndTime(QString group, QString time)
//{
//    Lesson* lesson = new Lesson();

//    queryModel->setQuery("SELECT * FROM DI_LESSONS WHERE (gruppa = '" + group +"' AND lesson_time='" + time + "');");
//    QString* naming = new QString(queryModel->index(0,0).data().toString());
//    lesson->setName(naming);
//    QString* lessonTime = new QString(queryModel->index(0,1).data().toString());
//    lesson->setLessonTime(lessonTime);
//    lesson->setGroup(&group);
//    lesson->setId(queryModel->index(0,3).data().toInt());
//    lesson->setAmount(queryModel->index(0,4).data().toInt());

//    QString teacherLogin = queryModel->index(0,5).data().toString();
//    queryModel->setQuery("SELECT * FROM DI_USERS WHERE login='" + teacherLogin +"';");

//    QString* teacherName = new QString(queryModel->index(0,3).data().toString());
//    lesson->setTeacher(teacherName);

//    return lesson;
//}

//void GeneralDAO::doSetVisit(QString studNum, int lessonId)
//{
//    QDate currentDate = QDate::currentDate();

//    QString query = "INSERT INTO DI_VISITINGS VALUES ("
//        + QString::number(lessonId) + ","
//        + "'" + studNum + "',"
//        + "'" + currentDate.toString("yyyy-MM-dd") + "');";
//    qDebug() << query;
//}

//GeneralDAO::GeneralDAO()
//{
//    db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("195.19.32.74");
//    db.setDatabaseName("fn1132_2020");
//    db.setPort(5432);
//    db.setUserName("student");
//    db.setPassword("bmstu");
//    db.open();

//    queryModel = new QSqlQueryModel(this);
//}
