#include "imagecathegorylist.h"

ImageCathegoryList::ImageCathegoryList(ImageCathegoryList* imageCathegoryList)
{
    *this = *imageCathegoryList;
}

ImageCathegoryList::ImageCathegoryList(QVector<QVariant> model)
{
    // init QVector
    this->list = new QVector<ImageCathegory*>();

    // generate ImageCathegory and add to list
    if(model.size()>1){
        for (int i = 0; i<model.size(); i++)
        {
            // create new ImageCathegory
            ImageCathegory* temp = new ImageCathegory(model.mid(i, 1));
            // add pointer to list
            this->list->append(temp);
        }
    }
}

int ImageCathegoryList::cathegoryZaehlen()
{
    return this->list->size();
}

ImageCathegory* ImageCathegoryList::cathegoryHolen(int i)
{
    return this->list->at(i);
}

void ImageCathegoryList::cathegoryEintragen(ImageCathegory* cat)
{
    this->list->append(cat);
}
