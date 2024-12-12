#include <QApplication>
#include <QDebug>
#include "auth/loginwindow.h"
#include "auth/registerwindow.h"
#include "ui/mainwindow.h"
#include "database/database.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize database
    Database* db = new Database();
    if (!db->connectToDatabase()) {
        qDebug() << "Failed to connect to database";
        return -1;
    }

    // Create windows
    LoginWindow* loginWindow = new LoginWindow(db);
    RegisterWindow* registerWindow = new RegisterWindow(db);
    MainWindow* mainWindow = nullptr;

    // Connect login/register windows
    QObject::connect(loginWindow, &LoginWindow::switchToRegister, [=]() {
        loginWindow->hide();
        registerWindow->show();
    });

    QObject::connect(registerWindow, &RegisterWindow::switchToLogin, [=]() {
        registerWindow->hide();
        loginWindow->show();
    });

    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [&mainWindow, db, loginWindow]() {
        loginWindow->hide();
        mainWindow = new MainWindow(db, loginWindow->getCurrentUsername());
        mainWindow->show();
    });

    loginWindow->show();

    return a.exec();
}
