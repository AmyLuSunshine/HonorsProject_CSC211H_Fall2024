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
    void validateEmail(const QString& email);

private:
    void setupUI();
    void setupStyles();
    bool isValidBMCCEmail(const QString& email);

    Database* database;
    QLineEdit* fullNameEdit;
    QLineEdit* emailEdit;
    QLineEdit* emplidEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QPushButton* registerButton;
    QPushButton* loginButton;
    QLabel* titleLabel;
    QLabel* errorLabel;
};
