#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <vector>
#include "models/job.h"
#include "models/user.h"

class Database : public QObject {
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool connectToDatabase();
    bool validateLogin(const QString& email, const QString& password);
    bool registerUser(const QString& fullName, const QString& password,
                      const QString& email, const QString& emplid,
                      const QString& major = "", const QString& gpa = "",
                      const QString& gradDate = "");

    bool updateProfile(const QString& email, const QString& major,
                       const QString& gpa, const QString& gradDate);

    User getUserData(const QString& email);
    std::vector<Job> getJobs();

private:
    QSqlDatabase db;
    bool createTables();
};
