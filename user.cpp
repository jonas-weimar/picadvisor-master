#include "user.h"

User::User(QVector<QVariant> model)
{
    // create user by model given by Database::find
    // the vectors variants must be converted to final types of User class
    // this is handeled hardcoded
    this->id = model[0].toInt();
    this->username = model[1].toString();
    this->password = model[2].toString();
    this->is_blocked = model[3].toBool();
    this->is_admin = model[4].toBool();
    this->created_at = model[5].toString();
    this->updated_at = model[6].toString();

    // set database table for this model
    this->table = this->getTable();
}

User::User(DatabaseAnswer<User>* response)
{
    *this = *response->getObject();
}

DatabaseAnswer<User>* User::create(QString username, QString password, bool is_blocked, bool is_admin, Database* db)
{
    // hash password
    password = QString(QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    // execute model
    DatabaseAnswer<User>* response = db->execModel<User>(User::generateSaveModel(username, password, is_blocked, is_admin));

    // check if response has error
    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<User>(User::generateFindModel(username, User::getTable()));
    }

    // return database answer
    return response;
}

bool User::validatePassword(QString password)
{
    // not validated yet
    bool validated = false;

    // hash given password
    password = QString(QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    // check if does match
    if(password == this->password){
        validated = true;
    }

    return validated;
}

QString User::getTable()
{
    return "tblUserAuth";
}

QString User::generateUpdateModel(int isBlocked)
{
    return "UPDATE " + User::getTable() + " SET is_blocked = " + QString::number(isBlocked) + " WHERE username LIKE '" + this->getUsername() + "'";
}

QString User::generateDeleteModel()
{
    return "DELETE FROM " + User::getTable() + " WHERE username LIKE '" + this->getUsername() + "'";
}

QString User::generateFindModel(QString username, QString table)
{
    return "SELECT * FROM " + table + " WHERE username LIKE '" + username + "'";
}

QString User::generateFindAllModel(QString table)
{
    return "SELECT * FROM " + table;
}

void User::isBlocked(bool b)
{
    this->is_blocked = b;
}

QString User::generateSaveModel(QString username, QString password, bool is_blocked, bool is_admin)
{
    // convert bool to int
    int isBlocked = (is_blocked) ? 1 : 0;
    int isAdmin = (is_admin) ? 1 : 0;

    // created at date
    QDate created_at = QDate::currentDate();
    QDate updated_at = created_at;

    // statement
    return "INSERT INTO " + User::getTable() + " (username, password, is_blocked, is_admin, created_at, updated_at) VALUES ('" + username + "', '" + password + "', " + QString::number(isBlocked) + ", " + QString::number(isAdmin) + ", '" + created_at.toString() + "', '" + updated_at.toString() + "')";
}
