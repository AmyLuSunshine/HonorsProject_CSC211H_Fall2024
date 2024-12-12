#pragma once
#include <QString>

class Job {
public:
    Job() = default;
    Job(int id, const QString& title, const QString& department,
        const QString& description, double payRate)
        : id(id), title(title), department(department),
        description(description), payRate(payRate) {}

    int getId() const { return id; }
    QString getTitle() const { return title; }
    QString getDepartment() const { return department; }
    QString getDescription() const { return description; }
    double getPayRate() const { return payRate; }

private:
    int id = -1;
    QString title;
    QString department;
    QString description;
    double payRate = 0.0;
};
