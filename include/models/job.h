#pragma once
#include <QString>

class Job {
public:
    Job(int id, const QString& title, const QString& department,
        const QString& description, double payRate, const QString& requirements = "",
        const QString& benefits = "", const QString& contactEmail = "")
        : id(id), title(title), department(department), description(description),
        payRate(payRate), requirements(requirements), benefits(benefits),
        contactEmail(contactEmail) {}

    int getId() const { return id; }
    QString getTitle() const { return title; }
    QString getDepartment() const { return department; }
    QString getDescription() const { return description; }
    double getPayRate() const { return payRate; }
    QString getRequirements() const { return requirements; }
    QString getBenefits() const { return benefits; }
    QString getContactEmail() const { return contactEmail; }

private:
    int id;
    QString title;
    QString department;
    QString description;
    double payRate;
    QString requirements;
    QString benefits;
    QString contactEmail;
};
