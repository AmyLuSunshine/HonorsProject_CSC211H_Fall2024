#include "models/user.h"

User::User(const QString& username, const QString& email,
           const QString& firstName, const QString& lastName)
    : username(username)
    , email(email)
    , firstName(firstName)
    , lastName(lastName)
    , createdAt(QDateTime::currentDateTime())
{}