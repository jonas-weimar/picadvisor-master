#ifndef FRMMAINMENU_H
#define FRMMAINMENU_H

#include <QWidget>

#include "frmstartgame.h"

#include "user.h"

namespace Ui {
class FrmMainMenu;
}

class FrmMainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMainMenu(QWidget* parent = 0);
    ~FrmMainMenu();

    // set previous widget and logged user
    void setPrevious(QWidget* previous);
    void setUser(User* user);

private slots:
    void on_btnLogout_clicked();

    void on_btnOpenPlayModal_clicked();

    void on_modalClosed_signal();

    void on_btnGoMenu_clicked();

    void on_btnOpenHelp_clicked();

private:
    Ui::FrmMainMenu *ui;

    // start game modal
    FrmStartGame *modal;

    // previous widget and user
    QWidget* previous;
    User* loggedUser;

    // window specific information
    const QString windowTitle = "Welcome to Picadvisor";
};

#endif // FRMMAINMENU_H
