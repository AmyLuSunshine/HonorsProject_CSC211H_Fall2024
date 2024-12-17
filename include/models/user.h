#pragma once
#include <QString>
#include <QDateTime>

class User {
public:
    User() = default;
    User(const QString& email, const QString& fullName,
         const QString& emplid, const QString& major = "",
         const QString& gpa = "", const QString& gradDate = "")
        : email(email), fullName(fullName), emplid(emplid),
        major(major), gpa(gpa), gradDate(gradDate) {}

    QString getEmail() const { return email; }
    QString getFullName() const { return fullName; }
    QString getEmplid() const { return emplid; }
    QString getMajor() const { return major; }
    QString getGpa() const { return gpa; }
    QString getGradDate() const { return gradDate; }

private:
    QString email;
    QString fullName;
    QString emplid;
    QString major;
    QString gpa;
    QString gradDate;
};
