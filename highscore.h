#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QVariant>
#include <QCryptographicHash>
#include "database.h"
#include "error.h"

class Highscore
{
private:

    QString token;
    int score;
    int id;
    int idUser;
    int idLevel;
    QDate created_at;
    QString table;
    static QString generateSaveModel(int score, int idLevel, int idUser, QString token);

public:
    Highscore(QVector<QVariant> model);
    Highscore(DatabaseAnswer<Highscore>* response);
    static QString getTable();
    static DatabaseAnswer<Highscore>* create(int score, int idLevel, int idUser);
    QString generateUpdateModel();
    static QString generateFindModel(QString token, QString table);
    static QString generateFindIdModel(int id, QString table);

    int getidUser(){ return this->idUser; }
    int getidLevel(){ return this->idLevel; }
    int getId() { return this->id; }
    QDate wasCreatedAt() { return this->created_at; }
    int getScore() { return this->score; }
    QString createToken() { return this->token; }
};


#endif // HIGHSCORE_H
