#include "frmstartgame.h"
#include "ui_frmstartgame.h"

FrmStartGame::FrmStartGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmStartGame)
{
    ui->setupUi(this);

    // create modal
    this->gameWindow = new FrmGameWindow();

    // signal for closed modal => frmstartgame
    connect(this->gameWindow,SIGNAL(gameClosed()),this,SLOT(on_gameWindow_closed()));
}

FrmStartGame::~FrmStartGame()
{
    delete ui;
}

void FrmStartGame::closeEvent(QCloseEvent *event)
{
    emit this->programCut();
}

void FrmStartGame::setDB(Database* db)
{
    this->db = db;
}

void FrmStartGame::setUp(Levelliste *list)
{
    // load level dropdown
    this->level = list;

    ui->cbxLevels->clear();

    for(int i = 0; i<this->level->levelZaehlen(); i++){
        ui->cbxLevels->addItem("Level " + QString::number(this->level->levelHolen(i)->getId()) + ": " + this->level->levelHolen(i)->getName());
    }

    // get cathegorys
    DatabaseAnswer<ImageCathegoryList>* respCat = this->db->find<ImageCathegoryList>(ImageCathegory::generateFindAllModel(ImageCathegory::getTable()));

    // check for error
    if(!respCat->hasError()){ this->cathegory = respCat->getObject(); } else { Error(500, "Query Error", respCat->errorToText()); }

    // delete pointer
    delete respCat;

    // load cathegory dropdown
    ui->cbxCategory->clear();

    for(int i = 0; i<this->cathegory->cathegoryZaehlen(); i++){
        ui->cbxCategory->addItem(this->cathegory->cathegoryHolen(i)->getName());
    }
}

void FrmStartGame::setUsername(QString username)
{
    this->username = username;
}

void FrmStartGame::on_btnStartGame_clicked()
{
    // get level and cathegory
    Level* currentLevel = this->level->levelHolen(ui->cbxLevels->currentIndex());
    ImageCathegory* currentCathegory = this->cathegory->cathegoryHolen(ui->cbxCategory->currentIndex());

    // emit signal that game started
    emit this->gameStarted();

    // set context of gamewindow
    this->gameWindow->setDB(this->db);
    this->gameWindow->setCathegory(currentCathegory);
    this->gameWindow->setLevel(currentLevel);
    this->gameWindow->setPlayer(username);

    // load game
    this->gameWindow->load();

    // show gamewindow and close this one
    this->gameWindow->show();
    this->close();
}

void FrmStartGame::on_gameWindow_closed()
{
    // emit signal that game ended
    emit this->gameClosed();
}
