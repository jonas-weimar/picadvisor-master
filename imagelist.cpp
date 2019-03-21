#include "imagelist.h"

ImageList::ImageList(ImageList* list)
{
    *this = *list;
}

ImageList::ImageList(QVector<QVariant> model)
{
    // init QVector
    this->list = new QVector<GameImage*>();

    // generate GameImage and add to list
    if(model.size()>1){
        for (int i = 0; i<model.size(); i=i+5)
        {
            // create new GameImage
            GameImage* temp = new GameImage(model.mid(i, 5));
            // add pointer to list
            this->list->append(temp);
        }
    }
}

int ImageList::imageZaehlen()
{
    return this->list->size();
}

GameImage* ImageList::imageHolen(int index)
{
    return this->list->at(index);
}

void ImageList::imageEintragen(GameImage* image)
{
    this->list->append(image);
}

void ImageList::imageRemove(int i)
{
    this->list->remove(i);
}
