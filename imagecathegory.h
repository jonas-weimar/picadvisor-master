#ifndef IMAGECATHEGORY_H
#define IMAGECATHEGORY_H

#include <QString>
#include <QVector>
#include <QVariant>


class ImageCathegory
{
public:
    ImageCathegory(QVector<QVariant> model);

    // get all cathegorys from tblImages
    static QString generateFindAllModel(QString table);
    static QString getTable(){ return "tblImages"; }

    // get attributes
    QString getName(){ return this->name; }

private:
    // attributes
    QString name;
};

#endif // IMAGECATHEGORY_H
