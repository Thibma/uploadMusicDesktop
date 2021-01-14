#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mediaPlayer = new QMediaPlayer;

    Theme anime("Opening d'animé");
    Theme chansons("Chansons");
    Theme films("Musique de films");

    themes.append(anime);
    themes.append(chansons);
    themes.append(films);

    for (int i = 0; i < themes.size(); i++) {
        ui->themeComboBox->addItem(themes[i].getName());
    }

    connect(ui->sendMusicPushButton, SIGNAL(clicked()), this, SLOT(sendMusic()));
    connect(ui->importImagePushButton, SIGNAL(clicked()), this, SLOT(importImage()));
    connect(ui->importMusicPushButton, SIGNAL(clicked()), this, SLOT(importMusic()));

    connect(ui->playPausePushButton, SIGNAL(clicked()), this, SLOT(playPause()));

    connect(mediaPlayer, SIGNAL(audioAvailableChanged(bool)), this, SLOT(audioAvailable(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMusic()
{
    qDebug() << "Musique envoyée !";
}

void MainWindow::importImage()
{
    qDebug() << "Importation";
    QFileDialog fileDialog;
    QString fileName = fileDialog.getOpenFileName(this, tr("Ouvrir l'image"), QDir::homePath(), tr("Images (*.png *.jpg)"));
    if (fileName.isEmpty()) {
        return;
    }
    ui->imageDetailLineEdit->setText(fileName);

    QPixmap image = fileName;
    ui->imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));



}

void MainWindow::importMusic()
{
    qDebug() << "Importation musique";
    QFileDialog fileDialog;
    QString fileName = fileDialog.getOpenFileName(this, tr("Ouvrir la musique"), QDir::homePath(), tr("Images (*.mp3 *.wav)"));
    if (fileName.isEmpty()) {
        return;
    }
    ui->musicUrlLineEdit->setText(fileName);

    mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
}

void MainWindow::playPause()
{
    if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
        mediaPlayer->stop();
    }
    else {
        mediaPlayer->play();
    }
}

void MainWindow::audioAvailable(bool available)
{
    ui->playPausePushButton->setEnabled(available);
}

