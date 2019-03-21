#include "levelliste.h"

Levelliste::Levelliste(Levelliste *levelList)
{
    *this = *levelList;
}

Levelliste::Levelliste(QVector<QVariant> model)
{
    // init QVector
    this->list = new QVector<Level*>();

    // generate level and add to list
    // highscore has 7 propertys so i = i + 7
    if(model.size()>1){
        for (int i = 0; i<model.size(); i=i+6)
        {
            // create new Level
            Level* temp = new Level(model.mid(i, 6));
            // add pointer to list
            this->levelEintragen(temp);
        }
    }
}

int Levelliste::levelZaehlen()
{
    return this->list->size();
}

Level* Levelliste::levelHolen(int index)
{
    return this->list->at(index);
}

void Levelliste::levelEintragen(Level* l)
{
    this->list->append(l);
}

void Levelliste::levelEntfernen(int index)
{
    delete this->list->at(index);
    this->list->remove(index);
}
