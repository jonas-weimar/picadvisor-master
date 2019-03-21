#ifndef GAMEIMAGE_H
#define GAMEIMAGE_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDate>

#include "database.h"
#include "error.h"
#include "databaseanswer.h"

class GameImage
{
public:
    GameImage(QVector<QVariant> model);
    GameImage(GameImage* response);

    // static get table
    static QString getTable(){ return "tblImages"; }

    // create Image
    static DatabaseAnswer<GameImage>* create(QString solution, QString path, QString cathegory, Database* db);

    // database helper methods
    QString generateDeleteModel(); // update existing image
    static QString generateFindModel(QString solution, QString cathegory, QString table);
    static QString generateFindAllByCathegoryModel(QString cathegory, QString table);
    static QString generateFindAllModel(QString table);

    // get attributes
    int getID(){ return this->id; }
    QString getSolution(){ return this->solution; }
    QString getPath(){ return this->path; }
    QString getCathegory(){ return this->cathegory; }
    QString wasCreatedAt(){ return this->created_at; }
    int getShowed(){ return this->image_showed; }
    void showed(){ this->image_showed = this->image_showed + 1; }
    QString toString(){
        return QString::number(this->getID()) + this->getSolution() + " Cathegory: " + this->getCathegory();
    }

private:
    // generate sql model to save this image
    static QString generateSaveModel(QString solution, QString path, QString cathegory);

    // attributes
    int id;
    QString solution;
    QString path;
    QString cathegory;
    QString created_at;

    int image_showed;
};

#endif // GAMEIMAGE_H
