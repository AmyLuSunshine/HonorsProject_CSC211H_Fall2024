#include "auth/registerwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

RegisterWindow::RegisterWindow(Database* db, QWidget *parent)
    : QWidget(parent), database(db) {
    setupUI();
    setupStyles();

    setWindowTitle("Register - Campus Jobs Portal");
    setFixedSize(400, 600);
}

void RegisterWindow::setupUI() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(50, 50, 50, 50);

    // Title
    titleLabel = new QLabel("Create Account", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Email
    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email (@stu.bmcc.cuny.edu)");
    mainLayout->addWidget(emailEdit);

    // Username
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    mainLayout->addWidget(usernameEdit);

    // First Name
    firstNameEdit = new QLineEdit(this);
    firstNameEdit->setPlaceholderText("First Name");
    mainLayout->addWidget(firstNameEdit);

    // Last Name
    lastNameEdit = new QLineEdit(this);
    lastNameEdit->setPlaceholderText("Last Name");
    mainLayout->addWidget(lastNameEdit);

    // Password
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);

    // Confirm Password
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Confirm Password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(confirmPasswordEdit);

    // Error label
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->hide();
    mainLayout->addWidget(errorLabel);

    // Register button
    registerButton = new QPushButton("Register", this);
    mainLayout->addWidget(registerButton);

    // Login link
    loginButton = new QPushButton("Already have an account? Login", this);
    mainLayout->addWidget(loginButton);

    // Connect signals
    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegistration);
    connect(loginButton, &QPushButton::clicked, this, &RegisterWindow::onLoginClicked);
}

void RegisterWindow::setupStyles() {
    setStyleSheet(
        "QWidget { background-color: #FFFFFF; }"
        "QLabel { font-size: 16px; color: #333333; }"  // Darkened label text
        "QLineEdit { padding: 10px; border: 2px solid #E0E0E0; border-radius: 5px; margin: 5px 0; "
        "           font-size: 14px; color: #333333; background-color: #FFFFFF; }"  // Fixed input text
        "QPushButton { padding: 10px; background-color: #2196F3; color: white; "
        "             border: none; border-radius: 5px; font-size: 14px; }"
        "QPushButton:hover { background-color: #1976D2; }"
        );

    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2196F3; margin: 20px 0;");
    loginButton->setStyleSheet(
        "QPushButton { background-color: transparent; color: #2196F3; }"
        "QPushButton:hover { color: #1976D2; }"
        );

    errorLabel->setStyleSheet("color: #D32F2F; font-size: 14px; margin-top: 10px;");  // Brighter red error text
}

void RegisterWindow::handleRegistration() {
    QString email = emailEdit->text();
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString confirmPass = confirmPasswordEdit->text();
    QString firstName = firstNameEdit->text();
    QString lastName = lastNameEdit->text();

    // Basic validation
    if (email.isEmpty() || username.isEmpty() || password.isEmpty() ||
        confirmPass.isEmpty() || firstName.isEmpty() || lastName.isEmpty()) {
        errorLabel->setText("All fields are required");
        errorLabel->show();
        return;
    }

    // Email validation
    if (!email.endsWith("@stu.bmcc.cuny.edu")) {
        errorLabel->setText("Must use @stu.bmcc.cuny.edu email");
        errorLabel->show();
        return;
    }

    // Password validation
    if (password.length() < 8) {
        errorLabel->setText("Password must be at least 8 characters");
        errorLabel->show();
        return;
    }

    if (password != confirmPass) {
        errorLabel->setText("Passwords do not match");
        errorLabel->show();
        return;
    }

    // Try to register
    if (database->registerUser(username, password, email, firstName, lastName)) {
        QMessageBox::information(this, "Success", "Registration successful! Please login.");
        emit registrationSuccessful();
        emit switchToLogin();
    } else {
        errorLabel->setText("Username or email already exists");
        errorLabel->show();
    }
}

void RegisterWindow::onLoginClicked() {
    emit switchToLogin();
}
