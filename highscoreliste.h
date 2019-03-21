#ifndef HIGHSCORELISTE_H
#define HIGHSCORELISTE_H
#include <QString>
#include "highscore.h"
#include <QVector>
#include <QVariant>

class Highscoreliste
{

private:

    QVector<Highscore*>* list;

public:

    Highscoreliste(){this->list = new QVector<Highscore*>();}
    Highscoreliste(Highscoreliste* highscoreList);
    Highscoreliste(QVector<QVariant> model);
    int highscoreZaehlen();
    void highscoreEintragen(Highscore* h);
    Highscore* highscoreHolen(int i);
};

#endif // HIGHSCORELISTE_H
