#ifndef USERLIST_H
#define USERLIST_H

#include <QString>
#include "user.h"
#include <QVector>
#include <QVariant>

class UserList
{

private:

    QVector<User*>* list;

public:

    UserList(UserList* userList);
    UserList(QVector<QVariant> model);
    int userZaehlen();
    void userEintragen(User* u);
    User* userHolen(int i);
    void userEntfernen(int index);
};

#endif // USERLIST_H
