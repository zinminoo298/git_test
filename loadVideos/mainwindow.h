#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>


namespace Ui {
class MainWindow;
}

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
    void on_pushButton_clicked();
private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);






private:
    QMediaPlayer *m_mediaPlayer = nullptr;
    QGraphicsVideoItem *m_videoItem = nullptr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
