#pragma once

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../database/database.h"
#include "../models/job.h"

class JobListWidget : public QWidget {
    Q_OBJECT
public:
    explicit JobListWidget(Database* db, QWidget *parent = nullptr);

private slots:
    void handleJobClicked(QListWidgetItem* item);
    void refreshJobs();
    void onJobSelected(int jobId);

private:
    void setupUI();
    void setupStyles();
    void loadJobs();
    QWidget* createJobCard(const Job& job);

    Database* database;
    QListWidget* jobList;
    QLabel* titleLabel;
    QPushButton* refreshButton;
    QVBoxLayout* mainLayout;
    std::vector<Job> currentJobs;
};
