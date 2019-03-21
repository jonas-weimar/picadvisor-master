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

    int id;
    QString token;
    int score;
    QString username;
    int idLevel;
    QString table;
    QString created_at;
    static QString generateSaveModel(int score, int idLevel, QString username, QString token);

public:
    Highscore(QVector<QVariant> model);
    Highscore(DatabaseAnswer<Highscore>* response);
    static QString getTable();
    static DatabaseAnswer<Highscore>* create(int score, int idLevel, QString username, Database* db);
    QString generateUpdateModel();
    static QString generateFindModel(QString token, QString table);
    static QString generateFindIdModel(int id, QString table);
    static QString generateFindAllModel(int idLevel, QString table);

    QString getUsername(){ return this->username; }
    int getidLevel(){ return this->idLevel; }
    int getId() { return this->id; }
    QString wasCreatedAt() { return this->created_at; }
    int getScore() { return this->score; }
    QString createToken() { return this->token; }
    QString toString(){ return QString::number(this->score) + " " + this->username + " " + this->created_at; }
};


#endif // HIGHSCORE_H
