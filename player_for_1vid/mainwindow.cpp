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
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setMinimumSize(760,350);
    ui->listWidget->setGridSize(QSize(360, 360));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setWrapping(true);

    //QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",

     //                                                 QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

    QString directory = QFileDialog::getOpenFileName(this,tr("Open File"),"All files(*.*)");
   // QMediaPlayer *mediaPlayer = new QMediaPlayer();
    //mediaPlayer = new QMediaPlayer();
    videoItem = new QGraphicsVideoItem;
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setMedia(QUrl::fromLocalFile(directory));

    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *graphicsView = new QGraphicsView(scene);
    scene->addItem(videoItem);

    mediaPlayer->setVideoOutput(videoItem);

    //player.append(mediaPlayer);



    m_playButton = new QPushButton;
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));


    m_positionSlider = new QSlider(Qt::Horizontal);
    m_positionSlider->setRange(0, 0);
    connect(m_playButton, &QAbstractButton::clicked, this, &MainWindow::play);
    connect(m_positionSlider, &QAbstractSlider::sliderMoved,this, &MainWindow::setPosition);

    connect(mediaPlayer, &QMediaPlayer::stateChanged, this, &MainWindow::mediaStateChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);

    auto    item = new QListWidgetItem("",ui->listWidget);
    auto    widget = new QWidget;
    //auto    label = new QLabel(finfo.fileName());
    auto    vb = new QVBoxLayout;

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_positionSlider);

    //vb->addWidget(label,1);
    vb->addWidget(graphicsView,9);
    vb->addLayout(controlLayout);
    widget->setLayout(vb);
    widget->setMinimumSize(340, 340);
    ui->listWidget->setItemWidget(item,widget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QSize MainWindow::sizeHint() const
{
    return (videoItem->size() * qreal(3) / qreal(2)).toSize();
}

bool MainWindow::isPlayerAvailable() const
{
    QMediaPlayer *mediaPlayer = player[1];
    return mediaPlayer->isAvailable();
}


void MainWindow::play()
{
    //QMediaPlayer *mediaPlayer = player[1];
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void MainWindow::positionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
}

void MainWindow::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, duration);
}

void MainWindow::setPosition(int position)
{
    //QMediaPlayer *mediaPlayer = player[1];
    mediaPlayer->setPosition(position);
}





