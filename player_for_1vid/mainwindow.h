#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QAbstractButton>
#include <QSlider>


namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QGraphicsVideoItem;
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();
    bool isPlayerAvailable() const;
    QSize sizeHint() const override;

public slots:
    void play();

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);






private:
    QVector<QMediaPlayer*> player;
    QMediaPlayer *mediaPlayer = nullptr;
    QMediaPlaylist *playlist = nullptr;
    QGraphicsVideoItem *videoItem = nullptr;
    QAbstractButton *m_playButton = nullptr;
    QSlider *m_positionSlider = nullptr;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
