#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
