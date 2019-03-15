#include "level.h"

Level::Level(QVector<QVariant> model)
{
    this->id = model[0].toInt();
    this->created_at = model[1].toDate();
    this->sekUmdrehen = model[2].toInt();
    this->gedrehtUm = model[3].toInt();
    this->strafZeit = model[4].toInt();

    this->table = this->getTable();
}

Level::Level(DatabaseAnswer<Level>* response)
{
    *this = *response->getObject();
}

DatabaseAnswer<Level>* Level::create(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit)
{
    Database* db = new Database;

    DatabaseAnswer<Level>* response = db->execModel<Level>(Level::generateSaveModel(name, sekUmdrehen, gedrehtUm, strafZeit));

    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<Level>(Level::generateFindModel(name, Level::getTable()));
    }

    delete db;

    return response;
}

QString Level::getTable()
{
    return "tblLevels";
}

QString Level::generateUpdateModel()
{
    return "";
}

QString Level::generateFindModel(QString name, QString table)
{
    return "SELECT * FROM " + table + " WHERE name LIKE '" + name + "'";
}

QString Level::generateFindIdModel(int id, QString table)
{
    return "SELECT * FROM " + table + " WHERE id = " + id;
}

QString Level::generateSaveModel(QString name, int sekUmdrehen, int gedrehtUm, int strafZeit)
{

    QDate created_at = QDate::currentDate();

    QString stmt = "INSERT INTO " + Level::getTable() + " (name, sekUmdrehen, gedrehtUm, strafZeit, created_at) VALUES ('" + name + "', " + sekUmdrehen + ", " + gedrehtUm + ", " + strafZeit + ", '" + created_at.toString() + "')";

    return stmt;
}
