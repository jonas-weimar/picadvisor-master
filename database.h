#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QCryptographicHash>
#include <QString>
#include <QApplication>

#include "databaseanswer.h"

class Database
{
public:
    Database();
    Database(QString path);
    ~Database();

    template<class T> DatabaseAnswer<T>* execModel(QString model);
    template<class T> DatabaseAnswer<T>* find(QString model);

private:
    QSqlDatabase db;
    QString path;
};

template<class T>
DatabaseAnswer<T>* Database::execModel(QString model)
{
    // model is an SQL statement (insert or update)
    // use QString model to create / update <model> in sqlite database
    // model is send by .saveModel() or .updateModel()

    // open database connection
    this->db.open();

    DatabaseAnswer<T>* response = new DatabaseAnswer<T>();;
    QSqlQuery query;
    bool ok;

    // execute model query
    ok = query.exec(model);

    // check if query got error
    if(!ok){
        response->setError(query.lastError().text());
    }

    // close database connection
    this->db.close();

    // return database answer
    return response;
}

template<class T>
DatabaseAnswer<T>* Database::find(QString model)
{
    // model is an SQL statement (select) returns one row!
    // QString model is used as the query
    // will create instance of <T> and return it
    // every model has a constructor for QVariant Vector
    // so Database::find can handle every type of Model ( User, Level, Highscore )

    // open database connection
    this->db.open();

    DatabaseAnswer<T>* response = new DatabaseAnswer<T>();
    QVector<QVariant> attributes;
    QSqlQuery query;
    bool ok;

    // execute model query
    ok = query.exec(model);

    if (!ok){
        response->setError(query.lastError().text());
    } else {
        ok = query.first();

        // create QVector<QVariant> for results
        for (int i = 0; i < query.record().count(); i++){
            attributes.append(query.value(i));
        }

        // create model
        T* modelPointer = new T(attributes);
        response->setObject(modelPointer);
    }

    // close database connection
    this->db.close();

    // return answer
    return response;
}

#endif // DATABASE_H
