#pragma once
#include <QString>
#include <QDateTime>

class User {
public:
    User() = default;
    User(const QString& username, const QString& email, 
         const QString& firstName, const QString& lastName);

    int getId() const { return id; }
    QString getUsername() const { return username; }
    QString getEmail() const { return email; }
    QString getFirstName() const { return firstName; }
    QString getLastName() const { return lastName; }
    QDateTime getCreatedAt() const { return createdAt; }

private:
    int id = -1;
    QString username;
    QString email;
    QString firstName;
    QString lastName;
    QDateTime createdAt;
};