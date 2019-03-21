#ifndef IMAGECATHEGORYLIST_H
#define IMAGECATHEGORYLIST_H

#include <QVector>

#include "imagecathegory.h"

class ImageCathegoryList
{
public:
    ImageCathegoryList(ImageCathegoryList* imageCathegoryList);
    ImageCathegoryList(QVector<QVariant> model);
    int cathegoryZaehlen();
    void cathegoryEintragen(ImageCathegory* cat);
    ImageCathegory* cathegoryHolen(int i);

private:
    QVector<ImageCathegory*>* list;
};

#endif // IMAGECATHEGORYLIST_H
