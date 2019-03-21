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

    // get table of class
    static QString getTable();

    // create user model
    static DatabaseAnswer<User>* create(QString username, QString password, bool is_blocked, bool is_admin, Database* db);

    // validate user password
    bool validatePassword(QString password);

    // database helper methods
    QString generateUpdateModel(int isBlocked); // update existing user
    QString generateDeleteModel();
    static QString generateFindModel(QString username, QString table); // find existing user
    static QString generateFindAllModel(QString table); // find existing user

    // setter methods
    void isBlocked(bool b);

    // getter methods
    int getId(){ return this->id; }
    QString getUsername(){ return this->username; }
    bool getIsBlocked(){ return this->is_blocked; }
    bool getIsAdmin(){ return this->is_admin; }
    QString wasCreatedAt(){ return this->created_at; }
    QString wasChangedAt(){ return this->updated_at; }
    QString toString(){
        QString isBlocked = this->getIsBlocked() ? "blocked" : "";
        return QString::number(this->getId()) + " " + this->username + " " + isBlocked;
    }


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
    QString created_at;
    QString updated_at;
};

#endif // USER_H
