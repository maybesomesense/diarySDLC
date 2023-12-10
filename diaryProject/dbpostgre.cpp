#include "dbpostgre.h"

QSqlDatabase initializeDb(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345");

    if (db.open()) {
            qDebug() << "Connected to database";
    } else {
        qDebug() << "Failed to connect to database";
    }

    return db;
}
