#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <Qvector>
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
    QDate created_at;
    int sekUmdrehen;
    int gedrehtUm;
    int strafZeit;
    QString table;
    static QString generateSaveModel(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit);

public:

    Level(QVector<QVariant> model);
    Level(DatabaseAnswer<Level>* response);
    static QString getTable();
    static DatabaseAnswer<Level>* create(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit);
    QString generateUpdateModel();
    static QString generateFindModel(QString name, QString table);
    static QString generateFindIdModel (int id, QString table);

    int getId() { return this->id; }
    QString getName() { return this->name; }
    QDate wasCreatedAt() { return this->created_at; }
    int getSekUmdrehen() { return this->sekUmdrehen; }
    int getGedrehtUm() { return this->gedrehtUm; }
    int getStrafZeit() { return this->strafZeit; }
    };

#endif // LEVEL_H
