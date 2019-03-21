#include "highscoreliste.h"

Highscoreliste::Highscoreliste(Highscoreliste *highscoreList)
{
    *this = *highscoreList;
}

Highscoreliste::Highscoreliste(QVector<QVariant> model)
{
    // init QVector
    this->list = new QVector<Highscore*>();

    // generate highscores and add to list
    if(model.size()>1){
        for (int i = 0; i<model.size(); i=i+6)
        {
            // create new Highscore
            Highscore* temp = new Highscore(model.mid(i, 6));
            // add pointer to list
            this->list->append(temp);
        }
    }
}

int Highscoreliste::highscoreZaehlen()
{
    return this->list->size();
}

Highscore* Highscoreliste::highscoreHolen(int index)
{
    return this->list->at(index);
}

void Highscoreliste::highscoreEintragen(Highscore* h)
{
    this->list->append(h);
}
