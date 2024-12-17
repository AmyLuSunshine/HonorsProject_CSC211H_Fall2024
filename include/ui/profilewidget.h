#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#endif // PROFILEWIDGET_H

#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../database/database.h"

class ProfileWidget : public QWidget {
    Q_OBJECT
public:
    explicit ProfileWidget(Database* db, QWidget *parent = nullptr);
    void loadUserProfile(const QString& username);

private:
    void setupUI();
    void setupStyles();

    Database* database;
    QLabel* usernameLabel;
    QLineEdit* emailEdit;
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QPushButton* saveButton;
};
