#include "frmmainmenu.h"
#include "ui_frmmainmenu.h"

FrmMainMenu::FrmMainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmMainMenu)
{
    ui->setupUi(this);

    // set focus of stacked widget to first page
    ui->mainStackedWidget->setCurrentIndex(0);

    // create modal
    this->modal = new FrmStartGame();

    // standard values
    this->hlist = new Highscoreliste();

    // signals for modal => frmstartgame
    connect(this->modal,SIGNAL(programCut()),this,SLOT(on_modalClosed_signal()));
    connect(this->modal,SIGNAL(gameStarted()),this,SLOT(on_gameStarted_signal()));
    connect(this->modal,SIGNAL(gameClosed()),this,SLOT(on_gameClosed_signal()));

    // set window title - size to 1100 x 630
    this->setWindowTitle(this->windowTitle);
    this->setFixedSize(QSize(1100,630));

    // set btnOpenAdmin false
    ui->btnOpenAdministration->setVisible(false);
}

FrmMainMenu::~FrmMainMenu()
{
    this->previous->close();
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

    if(this->loggedUser->getIsBlocked()){
        ui->btnOpenPlayModal->setEnabled(false);
    }
}

void FrmMainMenu::setDB(Database *db)
{
    this->db = db;
}

void FrmMainMenu::setUpNow()
{
    // load highscores of default level and levels
    DatabaseAnswer<Highscoreliste>* respHigh = this->db->find<Highscoreliste>(Highscore::generateFindAllModel(1, Highscore::getTable()));
    DatabaseAnswer<Levelliste>* respLevel = this->db->find<Levelliste>(Level::generateFindAllModel(Level::getTable()));
    DatabaseAnswer<UserList>* respUser = this->db->find<UserList>(User::generateFindAllModel(User::getTable()));
    DatabaseAnswer<ImageList>* respImage = this->db->find<ImageList>(GameImage::generateFindAllModel(GameImage::getTable()));

    // check if error then load highscores
    if(!respHigh->hasError()){ this->hlist = respHigh->getObject(); this->loadHighscoresWidget(); } else { Error(500, "Query Error Highscores", respHigh->errorToText()); }
    if(!respLevel->hasError()){ this->llist = respLevel->getObject(); } else { Error(500, "Query Error Level", respLevel->errorToText()); }
    if(!respUser->hasError()){ this->ulist = respUser->getObject(); } else { Error(500, "Query Error User", respUser->errorToText()); }
    if(!respImage->hasError()){ this->ilist = respImage->getObject(); } else { Error(500, "Query Error Images", respImage->errorToText()); }

    // delete responses
    delete respHigh;
    delete respLevel;
    delete respUser;
    delete respImage;

    // load dropdown
    this->loadLevelDropdown();

}

void FrmMainMenu::loadLevelDropdown()
{
    // clear cbxLevels
    ui->cbxLevels->clear();

    for(int i = 0; i<this->llist->levelZaehlen(); i++){
        ui->cbxLevels->addItem("Level " + QString::number(this->llist->levelHolen(i)->getId()) + ": " + this->llist->levelHolen(i)->getName());
    }
}

void FrmMainMenu::loadHighscoresByLevel(int idLevel)
{
    ui->lwHighscores->clear();

    // grep highscores from database
    DatabaseAnswer<Highscoreliste>* respHigh = this->db->find<Highscoreliste>(Highscore::generateFindAllModel(idLevel, Highscore::getTable()));

    // check for error
    if(!respHigh->hasError()){ this->hlist = respHigh->getObject(); } else { Error(500, "Query Error", respHigh->errorToText()); ui->cbxLevels->setCurrentIndex(0); }

    // delete database answer
    delete respHigh;

    // load into widget
    this->loadHighscoresWidget();
}

void FrmMainMenu::loadHighscoresWidget()
{
    // clear lwHighscores
    ui->lwHighscores->clear();

    // load introductry sentence into lw
    QListWidgetItem* intro = new QListWidgetItem("Highscores: \n");
    intro->setTextAlignment(Qt::AlignHCenter);
    ui->lwHighscores->addItem(intro);

    QListWidgetItem* item;
    for(int i = 0; i<this->hlist->highscoreZaehlen(); i++){
        item = new QListWidgetItem(this->hlist->highscoreHolen(i)->toString());
        item->setTextAlignment(Qt::AlignHCenter);

        ui->lwHighscores->addItem(item);
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

    // set modal attributes
    this->modal->setDB(this->db);
    this->modal->setUp(this->llist);
    this->modal->setUsername(this->loggedUser->getUsername());

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

void FrmMainMenu::on_gameStarted_signal()
{
    this->setVisible(false);
}

void FrmMainMenu::on_gameClosed_signal()
{
    this->setVisible(true);
    this->setEnabled(true);
    this->loadHighscoresByLevel(1);
}

void FrmMainMenu::on_btnGoMenu_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}

void FrmMainMenu::on_cbxLevels_currentIndexChanged(const QString &arg1)
{
    // all digits?
    QRegExp re("\\d*");

    // create prototype
    QString prototype = arg1.split(" ")[1].split(":")[0];

    // get level id or take first level
    int idLevel = re.exactMatch(prototype) ? arg1.split(" ")[1].split(":")[0].toInt() : 1;

    // load highscores
    this->loadHighscoresByLevel(idLevel);
}

void FrmMainMenu::loadShowUser()
{
    ui->lwShowUsers->clear();

    for(int i = 0; i<this->ulist->userZaehlen(); i++)
    {
        ui->lwShowUsers->addItem(this->ulist->userHolen(i)->toString());
    }
}

void FrmMainMenu::loadShowLevel()
{
    ui->lwShowLevel->clear();

    for(int i = 0; i<this->llist->levelZaehlen(); i++)
    {
        ui->lwShowLevel->addItem(this->llist->levelHolen(i)->toString());
    }
}

void FrmMainMenu::loadShowImages()
{
    ui->lwShowImages->clear();

    for(int i = 0; i<this->ilist->imageZaehlen(); i++)
    {
        ui->lwShowImages->addItem(this->ilist->imageHolen(i)->toString());
    }
}

void FrmMainMenu::on_btnOpenAdministration_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}

void FrmMainMenu::on_btnGoMenu_2_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}

void FrmMainMenu::on_btnGoAdministration_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}

void FrmMainMenu::on_btnManageUsers_clicked()
{
    this->loadShowUser();
    ui->mainStackedWidget->setCurrentIndex(3);
}

void FrmMainMenu::on_btnCreateNewUser_clicked()
{
    // get username, password and isAdmin
    QString userName = ui->edtUsername->text();
    QString userPassword = ui->edtPassword->text();
    int isAdmin = ui->cbIsAdmin->isChecked() ? 1 : 0;

    // clear edts
    ui->edtUsername->clear();
    ui->edtPassword->clear();
    ui->cbIsAdmin->clearFocus();

    // create user now
    DatabaseAnswer<User>* response = User::create(userName, userPassword, 0, isAdmin, this->db);

    // check for error
    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->ulist->userEintragen(new User(response));
    }

    // reload lwShowUser
    this->loadShowUser();
}

void FrmMainMenu::on_lwShowUsers_itemClicked(QListWidgetItem *item)
{
    ui->gbxChangeUser->setEnabled(true);
}

void FrmMainMenu::on_btnDeleteUser_clicked()
{
    // get current index
    int index = ui->lwShowUsers->currentRow();

    if(this->ulist->userHolen(index)->getIsAdmin()){
        // check if is last
        int count = 0;
        for(int i=0; i<this->ulist->userZaehlen(); i++)
        {
            count += this->ulist->userHolen(i)->getIsAdmin() ? 1: 0;
        }

        if (count > 1)
        {
            DatabaseAnswer<User>* response = this->db->execModel<User>(this->ulist->userHolen(index)->generateDeleteModel());

            if(response->hasError()){
                Error(500, "Query Error", response->errorToText());
            } else {
                this->ulist->userEntfernen(index);
            }
        } else {
            // cannot delete last administrator
            Error(500, "Last Admin Error", "Can't delete last admin.");
        }
    } else {
        DatabaseAnswer<User>* response = this->db->execModel<User>(this->ulist->userHolen(index)->generateDeleteModel());

        if(response->hasError()){
            Error(500, "Query Error", response->errorToText());
        } else {
            this->ulist->userEntfernen(index);
        }
    }

    // reload showUser
    this->loadShowUser();

    // disable gbx again
    ui->gbxChangeUser->setEnabled(false);
}

void FrmMainMenu::on_btnBlockUser_clicked()
{
    // get current index
    int index = ui->lwShowUsers->currentRow();

    // block user
    int isBlocked = 1;

    DatabaseAnswer<User>* response = this->db->execModel<User>(this->ulist->userHolen(index)->generateUpdateModel(isBlocked));

    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->ulist->userHolen(index)->isBlocked(true);
    }

    // reload showUser
    this->loadShowUser();

    // disable gbx again
    ui->gbxChangeUser->setEnabled(false);
}

void FrmMainMenu::on_btnUnblockUser_clicked()
{
    // get current index
    int index = ui->lwShowUsers->currentRow();

    // block user
    int isBlocked = 0;

    DatabaseAnswer<User>* response = this->db->execModel<User>(this->ulist->userHolen(index)->generateUpdateModel(isBlocked));

    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->ulist->userHolen(index)->isBlocked(false);
    }

    // reload showUser
    this->loadShowUser();

    // disable gbx again
    ui->gbxChangeUser->setEnabled(false);
}

void FrmMainMenu::on_btnManageLevel_clicked()
{
    this->loadShowLevel();
    ui->mainStackedWidget->setCurrentIndex(4);
}

void FrmMainMenu::on_btnGoAdministration_2_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}

void FrmMainMenu::on_btnCreateLevel_clicked()
{
    // attributes
    QString levelName = ui->edtLevelname->text();
    int sekUmdrehen = ui->edtLevelRectTurn->text().toInt() > 0 ? ui->edtLevelRectTurn->text().toInt() : 3;
    int gedrehtUm = ui->edtTurnedDeg->text().toInt();
    int strafZeit = ui->edtPunitiveTime->text().toInt();

    ui->edtLevelname->clear();
    ui->edtLevelRectTurn->clear();
    ui->edtTurnedDeg->clear();
    ui->edtPunitiveTime->clear();

    DatabaseAnswer<Level>* response = Level::create(levelName, sekUmdrehen, gedrehtUm, strafZeit, this->db);


    // check for error
    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->llist->levelEintragen(new Level(response));
    }

    // reload lwShowUser
    this->loadShowLevel();
}

void FrmMainMenu::on_btnDeleteLevel_clicked()
{
    // get current index
    int index = ui->lwShowLevel->currentRow();

    if(this->llist->levelZaehlen()>1)
    {
        DatabaseAnswer<Level>* response = this->db->execModel<Level>(this->llist->levelHolen(index)->generateDeleteModel());

        if(response->hasError()){
            Error(500, "Query Error", response->errorToText());
        } else {
            this->llist->levelEntfernen(index);
        }
    } else {
        Error(500, "Last Level", "Can't delete last level");
    }

    // reload showUser
    this->loadShowLevel();

    // disable gbx again
    ui->gbxChangeLevel->setEnabled(false);
}

void FrmMainMenu::on_btnDeleteHighscores_clicked()
{
    // get current index
    int index = ui->lwShowLevel->currentRow();

    DatabaseAnswer<Level>* response = this->db->execModel<Level>(this->llist->levelHolen(index)->generateDeleteHighscoresModel(Highscore::getTable()));

    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    }
    // reload showUser
    this->loadShowLevel();

    // disable gbx again
    ui->gbxChangeLevel->setEnabled(false);
}

void FrmMainMenu::on_lwShowLevel_itemClicked(QListWidgetItem *item)
{
    ui->gbxChangeLevel->setEnabled(true);
}

void FrmMainMenu::on_btnOpenFileDialog_clicked()
{
    this->createImagePath = QFileDialog::getOpenFileName(this,
            tr("Load Image"), "",
            tr("JPG Format (*.jpg);;PNG Format (*.png)"));

    ui->btnOpenFileDialog->setText(this->createImagePath.split("/").last());
}

void FrmMainMenu::on_btnManageImages_clicked()
{
    this->loadShowImages();
    ui->mainStackedWidget->setCurrentIndex(5);
}

void FrmMainMenu::on_lwShowImages_itemClicked(QListWidgetItem *item)
{
    ui->gbxChangeImage->setEnabled(true);
}

void FrmMainMenu::on_btnDeleteImage_clicked()
{
    // get current index
    int index = ui->lwShowImages->currentRow();

    DatabaseAnswer<GameImage>* response = this->db->execModel<GameImage>(this->ilist->imageHolen(index)->generateDeleteModel());

    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->ilist->imageRemove(index);
    }

    // reload showUser
    this->loadShowImages();

    // disable gbx again
    ui->gbxChangeImage->setEnabled(false);
}

void FrmMainMenu::on_btnCreateImage_clicked()
{
    // get username, password and isAdmin
    QString imageSolution = ui->edtImageSolution->text();
    QString imageCathegory = ui->edtImageCathegory->text();

    // clear edts
    ui->edtImageSolution->clear();
    ui->edtImageCathegory->clear();

    // create user now
    DatabaseAnswer<GameImage>* response = GameImage::create(imageSolution, this->createImagePath, imageCathegory, this->db);

    // check for error
    if(response->hasError()){
        Error(500, "Query Error", response->errorToText());
    } else {
        this->ilist->imageEintragen(new GameImage(response->getObject()));
    }

    // reload lwShowUser
    this->loadShowImages();
}

void FrmMainMenu::on_btnGoAdministration_3_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}
