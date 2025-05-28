#include "VideoPlayer.h"
#include <QVBoxLayout>
#include "ImageLabeler.h"
VideoPlayer::VideoPlayer(QWidget *parent)
    : QMainWindow(parent),
    mediaPlayer(new QMediaPlayer(this)),
    videoWidget(new QVideoWidget(this)) {

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    captureButton = new QPushButton("Capturar imagen", this);

    connect(playButton, &QPushButton::clicked, this, &VideoPlayer::play);
    connect(pauseButton, &QPushButton::clicked, this, &VideoPlayer::pause);
    connect(stopButton, &QPushButton::clicked, this, &VideoPlayer::stop);
    connect(captureButton, &QPushButton::clicked, this, &VideoPlayer::captureFrame);

    layout->addWidget(videoWidget);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);
    layout->addWidget(captureButton);

    setCentralWidget(centralWidget);
    mediaPlayer->setVideoOutput(videoWidget);

    openVideo();  // abre al iniciar
}

void VideoPlayer::openVideo() {
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir video");
    if (!fileName.isEmpty()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    }
}

void VideoPlayer::play() {
    mediaPlayer->play();
}

void VideoPlayer::pause() {
    mediaPlayer->pause();
}

void VideoPlayer::stop() {
    mediaPlayer->stop();
}

void VideoPlayer::captureFrame() {
    QPixmap frame = videoWidget->grab();
    QString path = QFileDialog::getSaveFileName(this, "Guardar imagen", "", "PNG Files (*.png)");
    if (!path.isEmpty()) {
        frame.save(path);
        (new ImageLabeler(path))->show();  // abre etiquetador
    }
}
