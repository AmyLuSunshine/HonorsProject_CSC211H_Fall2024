#pragma once
#include <QString>
#include <QDateTime>

class Application {
public:
    Application() = default;
    Application(int userId, int jobId)
        : userId(userId), jobId(jobId),
        createdAt(QDateTime::currentDateTime()) {}

private:
    int id = -1;
    int userId;
    int jobId;
    QString status = "pending";
    QDateTime createdAt;
};
