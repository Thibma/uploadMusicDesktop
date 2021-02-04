#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMediaPlayer>

#include "theme.h";
#include "music.h"
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getThemesOk();
    void sendMusicOk();

    void sendMusic();
    void sendDetailOk();

    void failed();

    void importImage();
    void importMusic();

    void playPause();

    void audioAvailable(bool available);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *mediaPlayer;
    QVector <Theme *> themes;

    Music *music;

    Network *network;

};
#endif // MAINWINDOW_H
