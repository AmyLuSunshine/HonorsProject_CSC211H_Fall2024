#include "ui/joblistwidget.h"
#include <QHBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include <algorithm>

JobListWidget::JobListWidget(Database* db, QWidget *parent)
    : QWidget(parent), database(db) {
    setupUI();
    setupStyles();
    loadJobs();
}

void JobListWidget::setupUI() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header section
    auto headerLayout = new QHBoxLayout();
    titleLabel = new QLabel("Available Campus Jobs", this);
    refreshButton = new QPushButton("Refresh", this);

    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(refreshButton);
    mainLayout->addLayout(headerLayout);

    // Jobs list
    jobList = new QListWidget(this);
    jobList->setSpacing(10);
    jobList->setViewMode(QListView::IconMode);
    jobList->setIconSize(QSize(300, 100));
    jobList->setMovement(QListView::Static);
    jobList->setResizeMode(QListView::Adjust);
    mainLayout->addWidget(jobList);

    // Connect signals
    connect(refreshButton, &QPushButton::clicked, this, &JobListWidget::refreshJobs);
    connect(jobList, &QListWidget::itemClicked, this, &JobListWidget::handleJobClicked);
}

void JobListWidget::setupStyles() {
    setStyleSheet(
        "QLabel { font-size: 24px; font-weight: bold; color: #2196F3; }"
        "QPushButton { padding: 8px 16px; background-color: #2196F3; color: white; "
        "             border: none; border-radius: 4px; }"
        "QPushButton:hover { background-color: #1976D2; }"
        "QListWidget { background-color: #F5F5F5; border: none; }"
        "QListWidget::item { background-color: white; border-radius: 8px; }"
        "QListWidget::item:hover { background-color: #E3F2FD; }"
        );
}

void JobListWidget::loadJobs() {
    jobList->clear();
    currentJobs = database->getJobs();

    for (const auto& job : currentJobs) {
        auto card = createJobCard(job);
        auto item = new QListWidgetItem(jobList);
        item->setSizeHint(card->sizeHint());
        jobList->setItemWidget(item, card);
        item->setData(Qt::UserRole, job.getId());
    }
}

void JobListWidget::refreshJobs() {
    loadJobs();
}

void JobListWidget::handleJobClicked(QListWidgetItem* item) {
    int jobId = item->data(Qt::UserRole).toInt();
    onJobSelected(jobId);
}

QWidget* JobListWidget::createJobCard(const Job& job) {
    auto card = new QWidget;
    card->setFixedWidth(300);
    auto layout = new QVBoxLayout(card);

    auto titleLabel = new QLabel(job.getTitle(), card);
    titleLabel->setStyleSheet("font-weight: bold; color: #1976D2;");

    auto deptLabel = new QLabel(job.getDepartment(), card);
    auto payLabel = new QLabel(QString("$%1/hr").arg(job.getPayRate(), 0, 'f', 2), card);
    payLabel->setStyleSheet("color: #4CAF50;");

    layout->addWidget(titleLabel);
    layout->addWidget(deptLabel);
    layout->addWidget(payLabel);

    card->setStyleSheet(
        "QWidget { background-color: white; border: 1px solid #E0E0E0; "
        "border-radius: 8px; padding: 10px; }"
        );

    return card;
}

void JobListWidget::onJobSelected(int jobId) {
    auto it = std::find_if(currentJobs.begin(), currentJobs.end(),
                           [jobId](const Job& job) { return job.getId() == jobId; });
    if (it != currentJobs.end()) {
        QMessageBox::information(this, "Job Selected",
                                 QString("Selected: %1\nDepartment: %2\nPay: $%3/hr")
                                     .arg(it->getTitle())
                                     .arg(it->getDepartment())
                                     .arg(it->getPayRate(), 0, 'f', 2));
    }
}
