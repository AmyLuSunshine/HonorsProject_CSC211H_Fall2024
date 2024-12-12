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
    bool validateLogin(const QString& username, const QString& password);
    bool registerUser(const QString& username, const QString& password,
                      const QString& email, const QString& firstName,
                      const QString& lastName);
    std::vector<Job> getJobs();
    User getUserData(const QString& username);
    bool createTables();

private:
    QSqlDatabase db;
};
