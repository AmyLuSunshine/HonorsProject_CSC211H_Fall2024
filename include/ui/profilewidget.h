#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#endif // PROFILEWIDGET_H


#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QFileDialog>
#include "../database/database.h"

class ProfileWidget : public QWidget {
    Q_OBJECT
public:
    explicit ProfileWidget(Database* db, QWidget *parent = nullptr);
    void loadUserProfile(const QString& username);

private slots:
    void handleSaveChanges();
    void handleOnboarding();
    void uploadTranscript();
    void uploadCV();

private:
    void setupUI();
    void setupStyles();
    void showDocumentStatus();

    Database* database;
    QLabel* nameLabel;
    QLineEdit* emplidEdit;
    QLineEdit* majorEdit;
    QLineEdit* gpaEdit;
    QDateEdit* gradDateEdit;

    // Document upload buttons
    QPushButton* uploadTranscriptBtn;
    QPushButton* uploadCVBtn;
    QLabel* transcriptLabel;
    QLabel* cvLabel;

    // Document tracking
    QLabel* pendingDocsLabel;
    QLabel* completedDocsLabel;
    QLabel* processingDocsLabel;

    QPushButton* saveButton;
    QPushButton* onboardingButton;

    // Status labels for required documents
    QLabel* i9StatusLabel;
    QLabel* w4StatusLabel;
    QLabel* ssnStatusLabel;
    QLabel* ddStatusLabel;  // Direct Deposit
};
