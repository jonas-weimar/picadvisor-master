#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <QVector>
#include <QVariant>

#include "database.h"
#include "gameimage.h"

class ImageList
{
public:
    ImageList(ImageList* imageList);
    ImageList(QVector<QVariant> model);
    int imageZaehlen();
    void imageEintragen(GameImage* image);
    void imageRemove(int i);
    GameImage* imageHolen(int i);

private:
    QVector<GameImage*>* list;
};

#endif // IMAGELIST_H
