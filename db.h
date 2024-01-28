#ifndef DB_H
#define DB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QVariant>
#include <QMap>

class Database {
private:
    QSqlDatabase db;

public:
    Database(const QString& path);
    ~Database();

    bool open();
    void close();
    QSqlQuery executeQuery(const QString& queryStr, const QMap<QString, QVariant>& params);
    QString lastError();
};

#endif // DB_H
