
#pragma once
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QFileDialog>


    class VideoPlayer : public QMainWindow {
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr);

private slots:
    void openVideo();
    void play();
    void pause();
    void stop();
    void captureFrame();

private:
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stopButton;
    QPushButton* captureButton;
};
