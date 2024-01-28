#include "db.h"
#include <QDebug>

Database::Database(const QString& path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

Database::~Database() {
    close();
}

bool Database::open() {
    if (!db.open()) {
        return false;
    }
    return true;
}

void Database::close() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlQuery Database::executeQuery(const QString& queryStr, const QMap<QString, QVariant>& params) {
    QSqlQuery query;
    query.prepare(queryStr);

    if(!params.isEmpty()){
        for(auto i = params.constBegin(); i != params.constEnd(); ++i){
            query.bindValue(i.key(), i.value());
        }
    }

    if(!query.exec()){
        qDebug() << "Error executing query:"<< query.lastError().text();
    }

    return query;
}

QString Database::lastError() {
    return db.lastError().text();
}
