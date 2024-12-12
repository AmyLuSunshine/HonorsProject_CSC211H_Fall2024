#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

Database::Database(QObject *parent)
    : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("campus_jobs.db");
}

Database::~Database() {
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::connectToDatabase() {
    if (!db.open()) {
        qDebug() << "Error connecting to database:" << db.lastError().text();
        return false;
    }
    return createTables();
}

bool Database::createTables() {
    QSqlQuery query;

    // Create users table
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "email TEXT UNIQUE NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
        );
    if (!success) return false;

    // Create jobs table
    success = query.exec(
        "CREATE TABLE IF NOT EXISTS jobs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "department TEXT NOT NULL,"
        "description TEXT NOT NULL,"
        "pay_rate REAL NOT NULL"
        ")"
        );
    if (!success) return false;

    // Insert sample job data if table is empty
    query.exec("SELECT COUNT(*) FROM jobs");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO jobs (title, department, description, pay_rate) VALUES "
                   "('Student Assistant', 'Computer Science', 'Help with lab sessions', 15.00),"
                   "('Library Assistant', 'Library', 'Help students find resources', 16.00),"
                   "('IT Support', 'IT Services', 'Provide technical support', 17.50)");
    }

    return true;
}

bool Database::validateLogin(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec() || !query.next()) {
        return false;
    }

    QString hashedPassword = QString(QCryptographicHash::hash(
                                         password.toUtf8(), QCryptographicHash::Sha256).toHex());
    return query.value(0).toString() == hashedPassword;
}

bool Database::registerUser(const QString& username, const QString& password,
                            const QString& email, const QString& firstName,
                            const QString& lastName) {
    QString hashedPassword = QString(QCryptographicHash::hash(
                                         password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, email, first_name, last_name) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashedPassword);
    query.addBindValue(email);
    query.addBindValue(firstName);
    query.addBindValue(lastName);

    return query.exec();
}

std::vector<Job> Database::getJobs() {
    std::vector<Job> jobs;
    QSqlQuery query;

    if (query.exec("SELECT * FROM jobs")) {
        while (query.next()) {
            jobs.emplace_back(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("department").toString(),
                query.value("description").toString(),
                query.value("pay_rate").toDouble()
                );
        }
    }

    return jobs;
}

User Database::getUserData(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        return User(
            query.value("username").toString(),
            query.value("email").toString(),
            query.value("first_name").toString(),
            query.value("last_name").toString()
            );
    }

    return User();
}
