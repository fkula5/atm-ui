#include "db.h"

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

QSqlQuery Database::query(const QString& queryStr) {
    QSqlQuery query;
    query.exec(queryStr);
    return query;
}

QString Database::lastError() {
    return db.lastError().text();
}
