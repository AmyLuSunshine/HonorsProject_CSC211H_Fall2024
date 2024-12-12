#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../database/database.h"

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(Database* db, QWidget *parent = nullptr);
    QString getCurrentUsername() const { return usernameEdit->text(); }


signals:
    void loginSuccessful();
    void switchToRegister();

private slots:
    void handleLogin();
    void onRegisterClicked();

private:
    void setupUI();
    void setupStyles();

    Database* database;
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QLabel* titleLabel;
    QLabel* errorLabel;
};
