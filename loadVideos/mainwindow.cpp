#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QApplication>
#include <QFileDialog>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",

     //                                                 QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

    QString directory = QFileDialog::getOpenFileName(this,tr("Open File"),"All files(*.*)");
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    m_videoItem = new QGraphicsVideoItem;
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(directory));
    m_videoItem->setSize(QSizeF(screenGeometry.width() / 3.2, screenGeometry.height() / 2.4));
    QGraphicsScene *scene = new QGraphicsScene(this);
    //QGraphicsView *graphicsView = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    scene->addItem(m_videoItem);


   // QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"All files(*.*)");
   // m_mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
   // ui->pushButton->setEnabled(false);
    ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(ui->pushButton, &QAbstractButton::clicked, this, &MainWindow::play);




    m_mediaPlayer->setVideoOutput(m_videoItem);
    connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
            this, &MainWindow::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);

    ui->horizontalSlider->setRange(0, 0);
    connect(ui->horizontalSlider, &QAbstractSlider::sliderMoved,
            this, &MainWindow::setPosition);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QSize MainWindow::sizeHint() const
{
    return (m_videoItem->size() * qreal(3) / qreal(2)).toSize();
}

bool MainWindow::isPlayerAvailable() const
{
    return m_mediaPlayer->isAvailable();
}


void MainWindow::play()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
}

void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void MainWindow::positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->horizontalSlider->setRange(0, duration);
}

void MainWindow::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
}


void MainWindow::on_pushButton_clicked()
{

   /* QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* vw =new QVideoWidget;
    player->setVideoOutput(vw);
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"All files(*.*)");
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,320,240);
    vw->show();
    player->play();*/
    //qDebug()<<player->state();
}


