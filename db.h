#ifndef DB_H
#define DB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>

class Database {
private:
    QSqlDatabase db;

public:
    Database(const QString& path);
    ~Database();

    bool open();
    void close();
    QSqlQuery query(const QString& queryStr);
    QString lastError();
};

#endif // DB_H
