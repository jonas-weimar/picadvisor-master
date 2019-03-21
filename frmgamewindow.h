#ifndef FRMGAMEWINDOW_H
#define FRMGAMEWINDOW_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QPixmap>
#include <QVector>
#include <QLabel>

#include "imagelist.h"
#include "error.h"
#include "database.h"
#include "imagecathegory.h"
#include "level.h"
#include "highscore.h"

namespace Ui {
class FrmGameWindow;
}

class FrmGameWindow : public QWidget
{
    Q_OBJECT
signals:
    void gameClosed();

public:
    explicit FrmGameWindow(QWidget *parent = nullptr);
    ~FrmGameWindow();

    void load();

    void setDB(Database* db);

    void setCathegory(ImageCathegory* cathegory);

    void setLevel(Level* level);

    void setPlayer(QString username);

private slots:
    void closeEvent(QCloseEvent *event);

    void updateUITimer();

    void turnRectangle();

    void on_edtSolution_returnPressed();

private:
    Ui::FrmGameWindow *ui;

    void endGame();

    void turnPixmap(int degrees);

    void constructOverlay();

    void calculateHighscore();

    void nextImage();

    int longestCommonSubsequence(QString X, QString, int m, int n);

    // game timer and update timer for ui
    QTimer* updateTimer;
    QTimer* turnRect;
    QElapsedTimer* gameTimer;

    // database
    Database* db;
    QString username;

    // window title
    const QString windowTitle = "Picadvisor Game";

    // game images list
    ImageList* images;
    int currentImage;

    // this level and cathegory
    ImageCathegory* cathegory;
    Level* level;

    // highscore specific
    Highscore* higscore;
    int punitiveTime = 0;

    QPixmap* picture;

    // overlay for the image
    QVector<QLabel*> overlay;
};

#endif // FRMGAMEWINDOW_H
