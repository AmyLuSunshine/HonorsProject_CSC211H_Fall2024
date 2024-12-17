#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QDateTime>

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

    // Create users table with new fields
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "full_name TEXT NOT NULL,"
        "email TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "emplid TEXT NOT NULL,"
        "major TEXT,"
        "gpa TEXT,"
        "grad_date TEXT,"
        "transcript_path TEXT,"
        "cv_path TEXT,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
        );
    if (!success) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }

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
    if (!success) {
        qDebug() << "Error creating jobs table:" << query.lastError().text();
        return false;
    }

    // Insert sample jobs if table is empty
    query.exec("SELECT COUNT(*) FROM jobs");
    if (query.next() && query.value(0).toInt() == 0) {
        success = query.exec(
            "INSERT INTO jobs (title, department, description, pay_rate) VALUES "
            "('Student Assistant', 'Computer Science', 'Help with lab sessions', 15.00),"
            "('Library Assistant', 'Library', 'Help students find resources', 16.00),"
            "('IT Support', 'IT Services', 'Provide technical support', 17.50)"
            );
        if (!success) {
            qDebug() << "Error inserting sample jobs:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

bool Database::validateLogin(const QString& email, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE email = ?");
    query.addBindValue(email);

    if (!query.exec() || !query.next()) {
        return false;
    }

    QString hashedPassword = QString(QCryptographicHash::hash(
                                         password.toUtf8(), QCryptographicHash::Sha256).toHex());
    return query.value(0).toString() == hashedPassword;
}

bool Database::registerUser(const QString& fullName, const QString& password,
                            const QString& email, const QString& emplid,
                            const QString& major, const QString& gpa,
                            const QString& gradDate) {
    QString hashedPassword = QString(QCryptographicHash::hash(
                                         password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO users (full_name, email, password, emplid, major, gpa, grad_date) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(fullName);
    query.addBindValue(email);
    query.addBindValue(hashedPassword);
    query.addBindValue(emplid);
    query.addBindValue(major);
    query.addBindValue(gpa);
    query.addBindValue(gradDate);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Error registering user:" << query.lastError().text();
    }
    return success;
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

User Database::getUserData(const QString& email) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = ?");
    query.addBindValue(email);

    if (query.exec() && query.next()) {
        return User(
            query.value("email").toString(),
            query.value("full_name").toString(),
            query.value("emplid").toString(),
            query.value("major").toString(),
            query.value("gpa").toString(),
            query.value("grad_date").toString()
            );
    }

    return User();
}

bool Database::updateProfile(const QString& email, const QString& major,
                             const QString& gpa, const QString& gradDate) {
    QSqlQuery query;
    query.prepare("UPDATE users SET major = ?, gpa = ?, grad_date = ? WHERE email = ?");
    query.addBindValue(major);
    query.addBindValue(gpa);
    query.addBindValue(gradDate);
    query.addBindValue(email);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Error updating profile:" << query.lastError().text();
    }
    return success;
}
