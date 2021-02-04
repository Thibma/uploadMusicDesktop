#include "network.h"

Network::Network()
{
    link = "https://api-4moc-blindtest.herokuapp.com";
    token = "?token=JbQzTPdnbMrsN9bwEsQCbRDvZmCRukKJcEQAhxusagUst";

    networkAccessManager = new QNetworkAccessManager();
}

void Network::getThemes()
{
    networkRequest.setUrl(QUrl(link + "/theme" + token));
    reply = networkAccessManager->get(networkRequest);
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinishedArray()));
}

void Network::postDetail(QString url, QString name)
{
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    textPart.setBody(name.toUtf8());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QFile *file = new QFile(url);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "failed";
    }
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+file->fileName().remove(0, file->fileName().lastIndexOf("/") + 1)+"\""));
    imagePart.setBodyDevice(file);
    file->setParent(multipart);

    multipart->append(imagePart);
    multipart->append(textPart);

    networkRequest.setUrl(QUrl(link + "/detail" + token));

    reply = networkAccessManager->post(networkRequest, multipart);
    multipart->setParent(reply);
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinishedObject()));
}

void Network::postMusic(QString url, QString name, QString idDetail, QString idTheme)
{
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    namePart.setBody(name.toUtf8());

    QHttpPart themePart;
    themePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    themePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"themeID\""));
    themePart.setBody(idTheme.toUtf8());

    QHttpPart detailPart;
    detailPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    detailPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"detailID\""));
    detailPart.setBody(idDetail.toUtf8());

    QHttpPart audioPart;
    audioPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/mp4"));
    QFile *file = new QFile(url);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "failed";
    }
    audioPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+file->fileName().remove(0, file->fileName().lastIndexOf("/") + 1)+"\""));
    audioPart.setBodyDevice(file);
    file->setParent(multipart);

    multipart->append(audioPart);
    multipart->append(namePart);
    multipart->append(themePart);
    multipart->append(detailPart);

    networkRequest.setUrl(QUrl(link + "/song" + token));

    reply = networkAccessManager->post(networkRequest, multipart);
    multipart->setParent(reply);
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinishedObject()));
}

QJsonDocument Network::getDocument()
{
    return documentReceive;
}

void Network::managerFinishedObject()
{
    disconnect(reply, SIGNAL(finished()), this, SLOT(managerFinishedObject()));
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (statusCode.isValid()) {
            QString status = statusCode.toString();
            if (status == "200") {
                QByteArray array = reply->readAll();
                QJsonDocument response = QJsonDocument::fromJson(array);
                QJsonObject jsonObject = response.object();
                bool error = jsonObject.value("error").toBool();
                QJsonObject message = jsonObject.value("message").toObject();

                if (error == true) {
                    QMessageBox error;
                    error.setText("Erreur d'input");
                    error.setInformativeText(reply->errorString());
                    error.setStandardButtons(QMessageBox::Ok);
                    error.setDefaultButton(QMessageBox::Ok);
                    error.setIcon(QMessageBox::Warning);
                    error.exec();
                    emit managerFailed();
                }

                documentReceive.setObject(message);
                qDebug() << documentReceive;

                emit managerGood();
            }
            else {
                QMessageBox error;
                error.setText("Erreur de connexion.");
                error.setInformativeText(reply->errorString());
                error.setStandardButtons(QMessageBox::Ok);
                error.setDefaultButton(QMessageBox::Ok);
                error.setIcon(QMessageBox::Warning);
                error.exec();
                emit managerFailed();
            }
        }
}

void Network::managerFinishedArray() {
    disconnect(reply, SIGNAL(finished()), this, SLOT(managerFinishedArray()));
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (statusCode.isValid()) {
            QString status = statusCode.toString();
            if (status == "200") {
                QByteArray array = reply->readAll();
                QJsonDocument response = QJsonDocument::fromJson(array);
                QJsonObject jsonObject = response.object();
                bool error = jsonObject.value("error").toBool();
                QJsonArray message = jsonObject.value("message").toArray();

                if (error == true) {
                    QMessageBox error;
                    error.setText("Erreur d'input");
                    error.setInformativeText(reply->errorString());
                    error.setStandardButtons(QMessageBox::Ok);
                    error.setDefaultButton(QMessageBox::Ok);
                    error.setIcon(QMessageBox::Warning);
                    error.exec();
                    emit managerFailed();
                }

                documentReceive.setArray(message);
                qDebug() << documentReceive;

                emit managerGood();
            }
            else {
                QMessageBox error;
                error.setText("Erreur de connexion.");
                error.setInformativeText(reply->errorString());
                error.setStandardButtons(QMessageBox::Ok);
                error.setDefaultButton(QMessageBox::Ok);
                error.setIcon(QMessageBox::Warning);
                error.exec();
                emit managerFailed();
            }
        }
}

