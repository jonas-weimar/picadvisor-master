#ifndef FRMSTARTGAME_H
#define FRMSTARTGAME_H

#include <QWidget>

#include "frmgamewindow.h"

#include "database.h"
#include "databaseanswer.h"
#include "levelliste.h"
#include "imagecathegorylist.h"

namespace Ui {
class FrmStartGame;
}

class FrmStartGame : public QWidget
{
    Q_OBJECT

signals:
    void programCut();

    void gameStarted();

    void gameClosed();

public:
    explicit FrmStartGame(QWidget *parent = nullptr);
    ~FrmStartGame();

    void setDB(Database* db);

    void setUp(Levelliste* list);

    void setUsername(QString username);

private slots:
    void closeEvent(QCloseEvent *event);

    void on_btnStartGame_clicked();

    void on_gameWindow_closed();

private:
    Ui::FrmStartGame *ui;

    // database
    Database* db;
    QString username;

    // container class levels
    Levelliste* level;
    ImageCathegoryList* cathegory;

    // game field
    FrmGameWindow* gameWindow;
};

#endif // FRMSTARTGAME_H
