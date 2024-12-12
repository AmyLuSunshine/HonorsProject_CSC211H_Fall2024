#include "ui/profilewidget.h"
#include <QVBoxLayout>
#include <QMessageBox>

ProfileWidget::ProfileWidget(Database* db, QWidget *parent)
    : QWidget(parent), database(db) {
    setupUI();
    setupStyles();
}

void ProfileWidget::setupUI() {
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(40, 40, 40, 40);

    auto titleLabel = new QLabel("My Profile", this);
    layout->addWidget(titleLabel);

    usernameLabel = new QLabel(this);
    layout->addWidget(usernameLabel);

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");
    layout->addWidget(emailEdit);

    firstNameEdit = new QLineEdit(this);
    firstNameEdit->setPlaceholderText("First Name");
    layout->addWidget(firstNameEdit);

    lastNameEdit = new QLineEdit(this);
    lastNameEdit->setPlaceholderText("Last Name");
    layout->addWidget(lastNameEdit);

    saveButton = new QPushButton("Save Changes", this);
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, &ProfileWidget::handleSaveClicked);

    layout->addStretch();
}

void ProfileWidget::setupStyles() {
    setStyleSheet(
        "QLabel { font-size: 16px; color: #333333; }"
        "QLineEdit { padding: 10px; border: 2px solid #E0E0E0; border-radius: 5px; }"
        "QPushButton { padding: 10px; background-color: #2196F3; color: white; "
        "             border: none; border-radius: 5px; }"
        );
}

void ProfileWidget::loadUserProfile(const QString& username) {
    usernameLabel->setText("Username: " + username);
}

void ProfileWidget::handleSaveClicked() {
    // TODO: Implement profile saving
    QMessageBox::information(this, "Success", "Profile updated successfully!");
}
