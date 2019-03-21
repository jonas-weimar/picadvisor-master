#include "frmgamewindow.h"
#include "ui_frmgamewindow.h"

FrmGameWindow::FrmGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmGameWindow)
{
    ui->setupUi(this);

    // set window title - size to 1100 x 630
    this->setWindowTitle(this->windowTitle);
    this->setFixedSize(QSize(1100,630));

    // timers for updating ui, gamefield and turning rectangle
    this->updateTimer = new QTimer(this);
    this->updateTimer->setInterval(1000);
    connect(this->updateTimer, SIGNAL(timeout()), this, SLOT(updateUITimer()));

    this->turnRect = new QTimer(this);
    connect(this->turnRect, SIGNAL(timeout()), this, SLOT(turnRectangle()));

    this->gameTimer = new QElapsedTimer();

    this->currentImage = 0;
}

FrmGameWindow::~FrmGameWindow()
{
    delete ui;
}

void FrmGameWindow::load()
{
    // get images
    DatabaseAnswer<ImageList>* response = this->db->find<ImageList>(GameImage::generateFindAllByCathegoryModel(this->cathegory->getName(), GameImage::getTable()));

    // has error
    if(!response->hasError()){ this->images = response->getObject(); } else { Error(500, "Query Error", response->errorToText()); }

    // delete responses
    delete response;

    // construct overlay
    this->constructOverlay();

    // choose random image
    this->currentImage = qrand() % (((this->images->imageZaehlen() - 1) + 1) - 0) + 0;
    this->images->imageHolen(this->currentImage)->showed();

    // create first image and activate showed
    this->picture = new QPixmap();

    this->picture->load(this->images->imageHolen(this->currentImage)->getPath());

    // turn image by levels degrees
    this->turnPixmap(this->level->getGedrehtUm());

    // create set first image and setScaledContents to true
    ui->lblShowImage->setPixmap(*this->picture);
    ui->lblShowImage->setScaledContents(true);

    // set interval to turn rectangluar overly
    this->turnRect->setInterval(this->level->getSekUmdrehen() * 1000);

    // start timers now
    this->updateTimer->start();
    this->turnRect->start();
    this->gameTimer->start();
}

void FrmGameWindow::setDB(Database *db)
{
    this->db = db;
}

void FrmGameWindow::setCathegory(ImageCathegory *cathegory)
{
    this->cathegory = cathegory;
}

void FrmGameWindow::setLevel(Level *level)
{
    this->level = level;
}

void FrmGameWindow::setPlayer(QString username)
{
    this->username = username;
}

void FrmGameWindow::closeEvent(QCloseEvent *event)
{
    emit this->gameClosed();
}

void FrmGameWindow::updateUITimer()
{
    // get time and format then print to label
    qint64 elapsed = this->gameTimer->elapsed();

    QString time = QString("%1:%2").arg( elapsed / 60000, 2, 10, QChar('0')).arg((elapsed % 60000) / 1000, 2, 10, QChar('0'));

    ui->lblTimer->setText(time);
}

void FrmGameWindow::turnRectangle()
{
    // seed from to
    int from(0);
    int to(this->overlay.size() - 1);

    // generate random index range(from, to)
    int index = qrand() % ((to + 1) - from) + from;

    // remove overlay at random index
    if(this->overlay.at(index)->isVisible())
    {
        this->overlay.at(index)->setVisible(false);
    } else {
        int proof = 0;

        for(int i=0; i<this->overlay.size(); i++)
        {
            if(!this->overlay.at(i)->isVisible())
            {
                proof++;
            }
        }

        if (proof == this->overlay.size())
        {
            this->punitiveTime += this->level->getStrafZeit();
            this->nextImage();
        } else {
            this->turnRectangle();
        }
    }
}

void FrmGameWindow::turnPixmap(int degrees)
{
    QTransform transform;
    transform = transform.rotate(degrees);

    this->picture = new QPixmap(this->picture->transformed(transform));
}

void FrmGameWindow::constructOverlay()
{
    // delete all overlays
    for(int i = 0; i<this->overlay.size(); i++)
    {
        delete this->overlay.at(i);
    }

    this->overlay.clear();

    // like (0|0) => (510|50)
    int x = 0;
    int y = 0;

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<5; i++)
        {
            QLabel* tmp = new QLabel(ui->lblShowImage);
            tmp->setGeometry(x, y, 105, 105);

            this->overlay.append(tmp);

            x = x + 105;
        }
        x = 0;
        y = y + 105;
    }
}

void FrmGameWindow::calculateHighscore()
{
    int elapsed = static_cast<int>(this->gameTimer->elapsed());
    int score = round(100000/(round(elapsed/1000) + this->punitiveTime));

    this->higscore->create(score, this->level->getId(), this->username, this->db);
}

void FrmGameWindow::nextImage()
{
    ui->edtSolution->clear();

    if(this->images->imageZaehlen() > 0){
        // choose next image
        this->currentImage = qrand() % (((this->images->imageZaehlen() - 1) + 1) - 0) + 0;

        if(this->images->imageHolen(this->currentImage)->getShowed() < 2)
        {
            this->images->imageHolen(this->currentImage)->showed();
            this->picture->load(this->images->imageHolen(this->currentImage)->getPath());

            // turn image by levels degrees
            this->turnPixmap(this->level->getGedrehtUm());

            // create set first image and setScaledContents to true
            ui->lblShowImage->setPixmap(*this->picture);
        } else {
            // delete object and remove pointer
            delete this->images->imageHolen(this->currentImage);
            this->images->imageRemove(this->currentImage);

            if(this->images->imageZaehlen() > 0)
            {
                // get new image
                this->nextImage();
            } else {
                this->endGame();
            }
        }
    } else {
        this->endGame();
    }

    // set all overlays to visible again
    for(int i=0; i<this->overlay.size(); i++)
    {
        this->overlay.at(i)->setVisible(true);
    }
}

int FrmGameWindow::longestCommonSubsequence(QString X, QString Y, int m, int n)
{
    if (m == 0 || n == 0)
    {
        return 0;
    }
    if (X[m - 1] == Y[n - 1])
    {
        return 1 + this->longestCommonSubsequence(X, Y, m - 1, n - 1);
    } else {
        int a = this->longestCommonSubsequence(X, Y, m, n - 1);
        int b = this->longestCommonSubsequence(X, Y, m - 1, n);

        return (a > b) ? a : b;
    }
}

void FrmGameWindow::on_edtSolution_returnPressed()
{
    // check if longest common subsequence is 80%
    // if yes next image if no add strafzeit
    QString solution = ui->edtSolution->text();
    int lcs = this->longestCommonSubsequence(solution, this->images->imageHolen(this->currentImage)->getSolution(), solution.size(), this->images->imageHolen(this->currentImage)->getSolution().size());

    // matches at least 85%
    if(lcs >= this->images->imageHolen(this->currentImage)->getSolution().size() * 0.85){
        this->nextImage();
    } else {
        this->punitiveTime += this->level->getStrafZeit();
    }
}

void FrmGameWindow::endGame()
{
    this->calculateHighscore();
    this->close();
}
