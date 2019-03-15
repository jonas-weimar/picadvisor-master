#include "highscore.h"

Highscore::Highscore(QVector<QVariant> model)
{
    this->id = model[0].toInt();
    this->score = model[1].toInt();
    this->created_at = model[2].toDate();
    this->idLevel = model[3].toInt();
    this->idUser = model[4].toInt();
    this->token = model[5].toString();

    this->table = this->getTable();
}

Highscore::Highscore(DatabaseAnswer<Highscore>* response)
{
    *this = *response->getObject();
}

DatabaseAnswer<Highscore>* Highscore::create(int score, int idLevel, int idUser)
{
    Database* db = new Database;

    QDateTime created_at = QDateTime::currentDateTime();

    QString tokenString = QString::number(score) + QString::number(idLevel) + QString::number(idUser) + created_at.toString();
    QString token = QString(QCryptographicHash::hash(tokenString.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    DatabaseAnswer<Highscore>* response = db->execModel<Highscore>(Highscore::generateSaveModel(score, idLevel, idUser, token));

    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<Highscore>(Highscore::generateFindModel(token, Highscore::getTable()));
    }

    delete db;

    return response;
}

QString Highscore::getTable()
{
    return "tblHighscores";
}

QString Highscore::generateUpdateModel()
{
    return "";
}

QString Highscore::generateFindModel(QString token, QString table)
{
    return "SELECT * FROM " + table + " WHERE token = '" + token + "'";
}

QString Highscore::generateFindIdModel(int id, QString table)
{
    return "SELECT * FROM " + table + " WHERE id = " + id;
}

QString Highscore::generateSaveModel(int score, int idLevel, int idUser, QString token)
{

    QDate created_at = QDate::currentDate();

    QString stmt = "INSERT INTO " + Highscore::getTable() + " (token, score, idLevel, idUser, created_at) VALUES ('" + token + "', '" + score + "', " + idLevel + ", " + idUser + ", '" + created_at.toString() + "')";

    return stmt;
}
