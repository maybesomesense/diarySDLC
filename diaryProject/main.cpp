#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlQuery>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "first");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345");

    if (db.open()) {
            qDebug() << "Connected to database";
            // Выполняйте SQL-запросы здесь
            db.close();
    } else {
        qDebug() << "Failed to connect to database";
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
