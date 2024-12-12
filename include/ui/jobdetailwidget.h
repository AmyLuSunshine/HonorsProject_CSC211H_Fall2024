#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "../database/database.h"
#include "../models/job.h"

class JobDetailWidget : public QWidget {
    Q_OBJECT
public:
    explicit JobDetailWidget(Database* db, QWidget *parent = nullptr);
    void setJob(const Job& job);

private:
    void setupUI();
    void setupStyles();

    Database* database;
    QLabel* titleLabel;
    QLabel* departmentLabel;
    QLabel* descriptionLabel;
    QLabel* payLabel;
    QPushButton* applyButton;
};
