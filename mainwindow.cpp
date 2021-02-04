#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralwidget->setEnabled(false);
    network = new Network();
    music = new Music(Details());
    mediaPlayer = new QMediaPlayer;

    connect(ui->sendMusicPushButton, SIGNAL(clicked()), this, SLOT(sendMusic()));
    connect(ui->importImagePushButton, SIGNAL(clicked()), this, SLOT(importImage()));
    connect(ui->importMusicPushButton, SIGNAL(clicked()), this, SLOT(importMusic()));

    connect(ui->playPausePushButton, SIGNAL(clicked()), this, SLOT(playPause()));

    connect(mediaPlayer, SIGNAL(audioAvailableChanged(bool)), this, SLOT(audioAvailable(bool)));

    network->getThemes();
    connect(network, SIGNAL(managerGood()), this, SLOT(getThemesOk()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getThemesOk()
{
    disconnect(network, SIGNAL(managerGood()), this, SLOT(getThemesOk()));
    QJsonDocument getMessage = network->getDocument();
    QJsonArray jsonArray = getMessage.array();
    foreach (const QJsonValue &v, jsonArray) {
        QJsonObject object = v.toObject();
        QString id = object.value("_id").toString();
        QString name = object.value("name").toString();

        themes.append(new Theme(id, name));
    }

    for (int i = 0; i < themes.size(); i++) {
        ui->themeComboBox->addItem(themes.at(i)->getName());
    }
    ui->centralwidget->setEnabled(true);
}

void MainWindow::sendMusic()
{
    if (ui->musicNameLineEdit->text().isEmpty() ||
            music->getFileUrl().isEmpty() ||
            ui->createDetailsLineEdit->text().isEmpty() ||
            music->getDetails().getUrl().isEmpty()) {
        QMessageBox error;
        error.setText("Attention.");
        error.setInformativeText("Merci de remplir tous les champs");
        error.setStandardButtons(QMessageBox::Ok);
        error.setDefaultButton(QMessageBox::Ok);
        error.setIcon(QMessageBox::Warning);
        error.exec();
        return;
    }
    ui->sendMusicPushButton->setEnabled(false);
    music->setMusicName(ui->musicNameLineEdit->text());
    music->getDetails().setName(ui->createDetailsLineEdit->text());
    network->postDetail(music->getDetails().getUrl(), music->getDetails().getName());
    connect(network, SIGNAL(managerFailed()), this, SLOT(failed()));
    connect(network, SIGNAL(managerGood()), this, SLOT(sendDetailOk()));
}

void MainWindow::sendDetailOk()
{
    disconnect(network, SIGNAL(managerFailed()), this, SLOT(failed()));
    disconnect(network, SIGNAL(managerGood()), this, SLOT(sendDetailOk()));
    QJsonDocument getResponse = network->getDocument();
    QJsonObject jsonObj = getResponse.object();
    QString id = jsonObj.value("_id").toString();
    network->postMusic(music->getFileUrl(), music->getMusicName(), id, themes.at(ui->themeComboBox->currentIndex())->getId());
    connect(network, SIGNAL(managerFailed()), this, SLOT(failed()));
    connect(network, SIGNAL(managerGood()), this, SLOT(sendMusicOk()));
}

void MainWindow::sendMusicOk() {
    disconnect(network, SIGNAL(managerFailed()), this, SLOT(failed()));
    disconnect(network, SIGNAL(managerGood()), this, SLOT(sendMusicOk()));
    ui->sendMusicPushButton->setEnabled(true);
    QMessageBox msg;
    msg.setText("Musique envoyée");
    msg.setInformativeText("La musique a bien été créer.");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void MainWindow::failed()
{
    ui->sendMusicPushButton->setEnabled(true);
}

void MainWindow::importImage()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getOpenFileName(this, tr("Ouvrir l'image"), QDir::homePath(), tr("Images (*.png *.jpg)"));
    if (fileName.isEmpty()) {
        return;
    }
    ui->imageDetailLineEdit->setText(fileName);

    QPixmap image = fileName;
    ui->imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    music->getDetails().setUrl(fileName);
    qDebug() << music->getDetails().getUrl() << fileName;
}

void MainWindow::importMusic()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getOpenFileName(this, tr("Ouvrir la musique"), QDir::homePath(), tr("Images (*.mp3 *.wav)"));
    if (fileName.isEmpty()) {
        return;
    }
    ui->musicUrlLineEdit->setText(fileName);

    mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));

    music->setfileUrl(fileName);
    qDebug() << music->getFileUrl();
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
