#include "auth/registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>

RegisterWindow::RegisterWindow(Database* db, QWidget *parent)
    : QWidget(parent), database(db) {
    setupUI();
    setupStyles();
}

void RegisterWindow::setupUI() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(50, 50, 50, 50);

    titleLabel = new QLabel("Create Account", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Email
    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("BMCC Email (@stu.bmcc.cuny.edu)");
    emailEdit->setMinimumHeight(40);
    mainLayout->addWidget(emailEdit);
    connect(emailEdit, &QLineEdit::textChanged, this, &RegisterWindow::validateEmail);

    // EMPLID
    emplidEdit = new QLineEdit(this);
    emplidEdit->setPlaceholderText("EMPLID");
    emplidEdit->setMinimumHeight(40);
    mainLayout->addWidget(emplidEdit);

    // Major
    majorEdit = new QLineEdit(this);
    majorEdit->setPlaceholderText("Major");
    majorEdit->setMinimumHeight(40);
    mainLayout->addWidget(majorEdit);

    // GPA
    gpaEdit = new QLineEdit(this);
    gpaEdit->setPlaceholderText("GPA");
    gpaEdit->setMinimumHeight(40);
    mainLayout->addWidget(gpaEdit);

    // Password
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(40);
    mainLayout->addWidget(passwordEdit);

    // Confirm Password
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Confirm Password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setMinimumHeight(40);
    mainLayout->addWidget(confirmPasswordEdit);

    // Error label
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->hide();
    mainLayout->addWidget(errorLabel);

    // Register button
    registerButton = new QPushButton("Register", this);
    registerButton->setMinimumHeight(40);
    mainLayout->addWidget(registerButton);

    // Login link
    loginButton = new QPushButton("Already have an account? Login", this);
    mainLayout->addWidget(loginButton);

    // Connect signals
    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegistration);
    connect(loginButton, &QPushButton::clicked, this, &RegisterWindow::onLoginClicked);

    setFixedSize(400, 700);
}

void RegisterWindow::setupStyles() {
    setStyleSheet(
        "QWidget { background-color: #FFFFFF; }"
        "QLabel { font-size: 16px; }"
        "QLineEdit { padding: 10px; border: 2px solid #E0E0E0; border-radius: 5px; "
        "           margin: 5px 0; font-size: 14px; color: #333333; }"
        "QPushButton { padding: 10px; background-color: #2196F3; color: white; "
        "             border: none; border-radius: 5px; font-size: 14px; }"
        "QPushButton:hover { background-color: #1976D2; }"
        );

    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2196F3; margin: 20px 0;");
    loginButton->setStyleSheet(
        "QPushButton { background-color: transparent; color: #2196F3; }"
        "QPushButton:hover { background-color: transparent; color: #1976D2; }"
        );
}

void RegisterWindow::handleRegistration() {
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    QString confirmPass = confirmPasswordEdit->text();
    QString emplid = emplidEdit->text();
    QString major = majorEdit->text();
    QString gpa = gpaEdit->text();

    // Validation
    if (!isValidBMCCEmail(email)) {
        errorLabel->setText("Must use @stu.bmcc.cuny.edu email");
        errorLabel->show();
        return;
    }

    if (password != confirmPass) {
        errorLabel->setText("Passwords do not match");
        errorLabel->show();
        return;
    }

    // Register user
    if (database->registerUser(email, password, email, emplid, major)) {
        QMessageBox::information(this, "Success", "Registration successful!");
        emit registrationSuccessful();
        emit switchToLogin();
    } else {
        errorLabel->setText("Registration failed. Email might already exist.");
        errorLabel->show();
    }
}

void RegisterWindow::onLoginClicked() {
    emit switchToLogin();
}

void RegisterWindow::validateEmail(const QString& email) {
    if (!email.isEmpty() && !isValidBMCCEmail(email)) {
        errorLabel->setText("Must use @stu.bmcc.cuny.edu email");
        errorLabel->show();
    } else {
        errorLabel->hide();
    }
}

bool RegisterWindow::isValidBMCCEmail(const QString& email) {
    return email.endsWith("@stu.bmcc.cuny.edu");
}
