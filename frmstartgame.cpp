#include "frmstartgame.h"
#include "ui_frmstartgame.h"

FrmStartGame::FrmStartGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmStartGame)
{
    ui->setupUi(this);
}

FrmStartGame::~FrmStartGame()
{
    this->previous->setDisabled(false);
    delete ui;
}

void FrmStartGame::closeEvent(QCloseEvent *event)
{
    emit this->programCut();
}
