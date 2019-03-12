#ifndef FRMSTARTGAME_H
#define FRMSTARTGAME_H

#include <QWidget>

namespace Ui {
class FrmStartGame;
}

class FrmStartGame : public QWidget
{
    Q_OBJECT

signals:
    void programCut();

public:
    explicit FrmStartGame(QWidget *parent = nullptr);
    ~FrmStartGame();

private slots:
    void closeEvent(QCloseEvent *event);

private:
    Ui::FrmStartGame *ui;

    // previous
    QWidget* previous;
};

#endif // FRMSTARTGAME_H
