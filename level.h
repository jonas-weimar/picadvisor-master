#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QVariant>
#include <QCryptographicHash>
#include "database.h"
#include "error.h"

class Level
{
private:

    int id;
    QString name;
    QString created_at;
    int sekUmdrehen;
    int gedrehtUm;
    int strafZeit;
    QString table;
    static QString generateSaveModel(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit);

public:

    Level(QVector<QVariant> model);
    Level(DatabaseAnswer<Level>* response);
    static QString getTable();
    static DatabaseAnswer<Level>* create(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit, Database* db);
    QString generateDeleteModel();
    QString generateDeleteHighscoresModel(QString table);
    static QString generateFindModel(QString name, QString table);
    static QString generateFindIdModel(int id, QString table);
    static QString generateFindAllModel(QString table);

    int getId() { return this->id; }
    QString getName() { return this->name; }
    QString wasCreatedAt() { return this->created_at; }
    int getSekUmdrehen() { return this->sekUmdrehen; }
    int getGedrehtUm() { return this->gedrehtUm; }
    int getStrafZeit() { return this->strafZeit; }
    QString toString(){
        return QString::number(this->getId()) + " " + this->getName() + " Turned: " + QString::number(this->getGedrehtUm()) + "deg";
    }
};

#endif // LEVEL_H
