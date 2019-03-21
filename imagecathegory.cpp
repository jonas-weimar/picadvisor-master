#include "imagecathegory.h"

ImageCathegory::ImageCathegory(QVector<QVariant> model)
{
    this->name = model[0].toString();
}

QString ImageCathegory::generateFindAllModel(QString table)
{
    return "SELECT cathegory FROM " + table + " GROUP BY cathegory";
}
