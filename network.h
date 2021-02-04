#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class Network : public QObject {

    Q_OBJECT

public:
    Network();

    void getThemes();
    void postDetail(QString url, QString name);
    void postMusic(QString url, QString name, QString idDetail, QString idTheme);

    QJsonDocument getDocument();

public slots:
    void managerFinishedObject();
    void managerFinishedArray();

signals:
    void managerGood();
    void managerBad();
    void managerFailed();

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest networkRequest;
    QNetworkReply *reply;

    QJsonDocument documentReceive;

    QString link;
    QString token;
};

#endif // NETWORK_H
