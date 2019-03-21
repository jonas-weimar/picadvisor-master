#include "highscore.h"

Highscore::Highscore(QVector<QVariant> model)
{
    this->id = model[0].toInt();
    this->score = model[1].toInt();
    this->username = model[2].toString();
    this->idLevel = model[3].toInt();
    this->token = model[4].toString();
    this->created_at = model[5].toString();

    this->table = this->getTable();
}

Highscore::Highscore(DatabaseAnswer<Highscore>* response)
{
    *this = *response->getObject();
}

DatabaseAnswer<Highscore>* Highscore::create(int score, int idLevel, QString username, Database* db)
{
    QDateTime created_at = QDateTime::currentDateTime();

    QString tokenString = QString::number(score) + QString::number(idLevel) + username + created_at.toString();
    QString token = QString(QCryptographicHash::hash(tokenString.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    DatabaseAnswer<Highscore>* response = db->execModel<Highscore>(Highscore::generateSaveModel(score, idLevel, username, token));

    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<Highscore>(Highscore::generateFindModel(token, Highscore::getTable()));
    }

    return response;
}

QString Highscore::getTable()
{
    return "tblHighscores";
}

QString Highscore::generateFindModel(QString token, QString table)
{
    return "SELECT * FROM " + table + " WHERE token = '" + token + "'";
}

QString Highscore::generateFindIdModel(int id, QString table)
{
    return "SELECT * FROM " + table + " WHERE id = " + QString::number(id);
}

QString Highscore::generateFindAllModel(int idLevel, QString table)
{
    return "SELECT * FROM " + table + " WHERE idLevel = " + QString::number(idLevel) + " ORDER BY score DESC";
}

QString Highscore::generateSaveModel(int score, int idLevel, QString username, QString token)
{

    QDate created_at = QDate::currentDate();

    return "INSERT INTO " + Highscore::getTable() + " (token, score, idLevel, username, created_at) VALUES ('" + token + "', '" + QString::number(score) + "', " + QString::number(idLevel) + ", '" + username + "', '" + created_at.toString() + "')";
}
