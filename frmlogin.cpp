#include "frmlogin.h"
#include "ui_frmlogin.h"

#include <QMessageBox>
#include <QCryptographicHash>

FrmLogin::FrmLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmLogin)
{
    ui->setupUi(this);

    // set window title - size to 1100 x 630
    this->setWindowTitle(this->windowTitle);
    this->setFixedSize(QSize(1100,630));

    // database is database
    this->db = new Database;
}

FrmLogin::~FrmLogin()
{
    delete ui;
    delete this->db;
}

void FrmLogin::on_btnLoginHelp_clicked()
{
    QMessageBox box;

    // set help modal title and text
    box.setWindowTitle("LogIn Help");
    box.setText(
                "To play a game you need to login with your player account.\n"
                "\n"
                "- If you have no account yet, please ask your administrator.\n"
                "- If you can't log in with your credentials, please contact\nyour administrator.\n"
                "- If you forgot any of your credentials, please ask your administrator."
    );

    // open help modal
    box.exec();
}

void FrmLogin::on_btnLogin_clicked()
{
    // get username and password
    QString uname = ui->edtUsername->text();
    QString pwd = ui->edtPassword->text();

    // clear ui fields
    ui->edtUsername->clear();
    ui->edtPassword->clear();

    // find user in database and get databaseanswer object<T> back
    DatabaseAnswer<User>* result = db->find<User>(User::generateFindModel(uname, User::getTable()));

    // check if has error
    if (result->hasError()){
        Error(500, "InternalError", result->errorToText());
    } else {
        if(result->getObject()->validatePassword(pwd)){
            // set this window to invisible
            this->setVisible(false);

            // create menu context
            FrmMainMenu* context = new FrmMainMenu();

            // set previous context and set logged user
            context->setPrevious(this);
            context->setUser(result->getObject());
            context->setDB(this->db);

            // setup context
            context->setUpNow();

            // delete response
            delete result;

            // show next context
            context->show();
        } else {
            Error(403, "Forbidden", "Your credentials couldn't be verified.");
        }
    }
}

void FrmLogin::on_edtPassword_returnPressed()
{
    // on enter check login credentials
    this->on_btnLogin_clicked();
}
