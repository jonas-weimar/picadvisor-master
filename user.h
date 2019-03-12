#ifndef USER_H
#define USER_H

#include <QCryptographicHash>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QDate>

#include "database.h"
#include "error.h"

class User
{
public:
    User(QVector<QVariant> model);
    User(DatabaseAnswer<User>* response);
    static QString getTable();

    // create user model
    static DatabaseAnswer<User>* create(QString username, QString password, bool is_blocked, bool is_admin);

    // validate user password
    bool validatePassword(QString password);

    // database helper methods
    QString generateUpdateModel(); // update existing user
    static QString generateFindModel(QString username, QString table); // find existing user

    // getter methods
    int getId(){ return this->id; }
    QString getUsername(){ return this->username; }
    bool getIsBlocked(){ return this->is_blocked; }
    bool getIsAdmin(){ return this->is_admin; }
    QDate wasCreatedAt(){ return this->created_at; }
    QDate wasChangedAt(){ return this->updated_at; }


private:
    // models database specific attributes
    QString table;

    // generate sql model to save this user
    static QString generateSaveModel(QString username, QString password, bool is_blocked, bool is_admin);

    // model private attributes
    int id;
    QString username;
    QString password;
    bool is_blocked;
    bool is_admin;
    QDate created_at;
    QDate updated_at;
};

#endif // USER_H
