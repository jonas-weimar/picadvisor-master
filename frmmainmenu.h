#ifndef FRMMAINMENU_H
#define FRMMAINMENU_H

#include <QWidget>
#include <QListWidgetItem>
#include <QFileDialog>

#include "frmstartgame.h"

#include "databaseanswer.h"
#include "database.h"
#include "userlist.h"
#include "highscoreliste.h"
#include "levelliste.h"
#include "imagelist.h"

namespace Ui {
class FrmMainMenu;
}

class FrmMainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMainMenu(QWidget* parent = 0);
    ~FrmMainMenu();

    void setPrevious(QWidget* previous);

    void setUser(User* user);

    void setDB(Database* db);

    void loadHighscoresByLevel(int idLevel);

    void setUpNow();

    void loadHighscoresWidget();

    void loadLevelDropdown();

private slots:
    void on_btnLogout_clicked();

    void on_btnOpenPlayModal_clicked();

    void on_modalClosed_signal();

    void on_gameStarted_signal();

    void on_gameClosed_signal();

    void on_btnGoMenu_clicked();

    void on_btnOpenHelp_clicked();

    void on_cbxLevels_currentIndexChanged(const QString &arg1);

    void on_btnOpenAdministration_clicked();

    void on_btnGoMenu_2_clicked();

    void on_btnGoAdministration_clicked();

    void on_btnManageUsers_clicked();

    void on_btnCreateNewUser_clicked();

    void on_lwShowUsers_itemClicked(QListWidgetItem *item);

    void on_btnDeleteUser_clicked();

    void on_btnBlockUser_clicked();

    void on_btnUnblockUser_clicked();

    void on_btnManageLevel_clicked();

    void on_btnGoAdministration_2_clicked();

    void on_btnCreateLevel_clicked();

    void on_btnDeleteLevel_clicked();

    void on_lwShowLevel_itemClicked(QListWidgetItem *item);

    void on_btnOpenFileDialog_clicked();

    void on_btnManageImages_clicked();

    void on_lwShowImages_itemClicked(QListWidgetItem *item);

    void on_btnDeleteImage_clicked();

    void on_btnCreateImage_clicked();

    void on_btnDeleteHighscores_clicked();

private:
    Ui::FrmMainMenu *ui;

    void loadShowUser();

    void loadShowLevel();

    void loadShowImages();

    // start game modal
    FrmStartGame *modal;

    // database connection
    Database* db;

    // previous widget and user
    QWidget* previous;
    User* loggedUser;

    // for image creation
    QString createImagePath = "";

    // window specific information
    const QString windowTitle = "Welcome to Picadvisor";

    // container classes
    Highscoreliste* hlist;
    Levelliste* llist;
    UserList* ulist;
    ImageList* ilist;
};

#endif // FRMMAINMENU_H
