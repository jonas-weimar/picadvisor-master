#include "frmmainmenu.h"
#include "ui_frmmainmenu.h"

#include "QDebug"

FrmMainMenu::FrmMainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmMainMenu)
{
    ui->setupUi(this);

    // set focus of stacked widget to first page
    ui->mainStackedWidget->setCurrentIndex(0);

    this->modal = new FrmStartGame();
    // signal for closed modal => frmstartgame
    connect(this->modal,SIGNAL(programCut()),this,SLOT(on_modalClosed_signal()));

    // set window title - size to 1100 x 630
    this->setWindowTitle(this->windowTitle);
    this->setFixedSize(QSize(1100,630));

    // set btnOpenAdmin false
    ui->btnOpenAdministration->setVisible(false);
}

FrmMainMenu::~FrmMainMenu()
{
    delete ui;
}

void FrmMainMenu::setPrevious(QWidget* previous)
{
    this->previous = previous;
}

void FrmMainMenu::setUser(User *user)
{
    this->loggedUser = user;

    // if user isAdmin show btnOpenAdmin
    if(this->loggedUser->getIsAdmin()){
        ui->btnOpenAdministration->setVisible(true);
    }
}

void FrmMainMenu::on_btnLogout_clicked()
{
    // exit this window and show login again
    this->previous->setVisible(true);
    this->close();
}

void FrmMainMenu::on_btnOpenPlayModal_clicked()
{
    // set this to disabled and as next modals previous
    this->setEnabled(false);
    // show modal
    this->modal->show();
}

void FrmMainMenu::on_btnOpenHelp_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(1);
}

void FrmMainMenu::on_modalClosed_signal()
{
    this->setEnabled(true);
}

void FrmMainMenu::on_btnGoMenu_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}
