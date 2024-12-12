#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../database/database.h"

class RegisterWindow : public QWidget {
    Q_OBJECT
public:
    explicit RegisterWindow(Database* db, QWidget *parent = nullptr);

signals:
    void registrationSuccessful();
    void switchToLogin();

private slots:
    void handleRegistration();
    void onLoginClicked();

private:
    void setupUI();
    void setupStyles();

    Database* database;
    QLineEdit* emailEdit;
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QPushButton* registerButton;
    QPushButton* loginButton;
    QLabel* titleLabel;
    QLabel* errorLabel;
};
