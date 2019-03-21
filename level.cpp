#include "level.h"

Level::Level(QVector<QVariant> model)
{
    this->id = model[0].toInt();
    this->name = model[1].toString();
    this->sekUmdrehen = model[2].toInt();
    this->gedrehtUm = model[3].toInt();
    this->strafZeit = model[4].toInt();
    this->created_at = model[5].toString();

    this->table = this->getTable();
}

Level::Level(DatabaseAnswer<Level>* response)
{
    *this = *response->getObject();
}

DatabaseAnswer<Level>* Level::create(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit, Database* db)
{
    DatabaseAnswer<Level>* response = db->execModel<Level>(Level::generateSaveModel(name, sekUmdrehen, gedrehtUm, strafZeit));

    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<Level>(Level::generateFindModel(name, Level::getTable()));
    }

    return response;
}

QString Level::getTable()
{
    return "tblLevels";
}

QString Level::generateDeleteModel()
{
    return "DELETE FROM " + Level::getTable() + " WHERE name LIKE '" + this->getName() + "'";
}

QString Level::generateDeleteHighscoresModel(QString table)
{
    return "DELETE FROM " + table + " WHERE idLevel = " + QString::number(this->getId());
}

QString Level::generateFindModel(QString name, QString table)
{
    return "SELECT * FROM " + table + " WHERE name LIKE '" + name + "'";
}

QString Level::generateFindIdModel(int id, QString table)
{
    return "SELECT * FROM " + table + " WHERE id = " + QString::number(id);
}

QString Level::generateFindAllModel(QString table)
{
    return "SELECT * FROM " + table;
}

QString Level::generateSaveModel(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit)
{

    QDate created_at = QDate::currentDate();

    return "INSERT INTO " + Level::getTable() + " (name, sekUmdrehen, gedrehtUm, strafZeit, created_at) VALUES ('" + name + "', " + QString::number(sekUmdrehen) + ", " + QString::number(gedrehtUm) + ", " + QString::number(strafZeit) + ", '" + created_at.toString() + "')";
}
