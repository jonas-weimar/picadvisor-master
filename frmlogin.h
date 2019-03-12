#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QWidget>

#include "frmmainmenu.h"

#include "databaseanswer.h"
#include "database.h"
#include "error.h"
#include "user.h"

namespace Ui {
class FrmLogin;
}

class FrmLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FrmLogin(QWidget *parent = 0);
    ~FrmLogin();

private slots:
    void on_btnLoginHelp_clicked();

    void on_btnLogin_clicked();

private:
    Ui::FrmLogin *ui;

    // database controller
    Database* db;

    // window specific information
    const QString windowTitle = "Welcome to Picadvisor";
};

#endif // FRMLOGIN_H
