#include "gameimage.h"

GameImage::GameImage(QVector<QVariant> model)
{
    this->id = model[0].toInt();
    this->solution = model[1].toString();
    this->path = model[2].toString();
    this->cathegory = model[3].toString();
    this->created_at = model[4].toString();

    this->image_showed = 0;
}

GameImage::GameImage(GameImage* response)
{
    *this = *response;
}

DatabaseAnswer<GameImage>* GameImage::create(QString solution, QString path, QString cathegory, Database* db)
{
    // execute model
    DatabaseAnswer<GameImage>* response = db->execModel<GameImage>(GameImage::generateSaveModel(solution, path, cathegory));

    // check if response has error
    if(response->hasError()){
        Error(500, "QueryError", response->errorToText());
    } else {
        response = db->find<GameImage>(GameImage::generateFindModel(solution, cathegory, GameImage::getTable()));
    }

    // return database answer
    return response;
}

QString GameImage::generateDeleteModel()
{
    return "DELETE FROM " + GameImage::getTable() + " WHERE solution LIKE '" + this->getSolution() + "'";
}

QString GameImage::generateFindModel(QString solution, QString cathegory, QString table)
{
    return "SELECT * FROM " + table + " WHERE solution LIKE '" + solution + "' AND cathegory LIKE '" + cathegory + "'";
}

QString GameImage::generateFindAllByCathegoryModel(QString cathegory, QString table)
{
    return "SELECT * FROM " + table + " WHERE cathegory LIKE '" + cathegory + "' ORDER BY RANDOM()";
}

QString GameImage::generateFindAllModel(QString table)
{
    return "SELECT * FROM " + table;
}

QString GameImage::generateSaveModel(QString solution, QString path, QString cathegory)
{
    // create statement with current date
    // insert into GameImage::getTable() => QString
    QString created_at = QDate::currentDate().toString();
    return "INSERT INTO " + GameImage::getTable() + " (solution, path, cathegory, created_at) VALUES ('" + solution + "', '" + path + "', '" + cathegory + "', '" + created_at + "')";
}
