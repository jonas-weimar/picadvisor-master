#ifndef LEVELLISTE_H
#define LEVELLISTE_H

#include <QVector>
#include <QVariant>
#include "level.h"

class Levelliste
{
private:

    QVector<Level*>* list;

public:

    Levelliste(Levelliste *levelList);
    Levelliste(QVector<QVariant> model);
    int levelZaehlen();
    Level* levelHolen(int index);
    void levelEintragen(Level* l);
    void levelEntfernen(int index);
};

#endif // LEVELLISTE_H
