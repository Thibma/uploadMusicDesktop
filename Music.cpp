#include "Music.h"

Music::Music()
{
    details = Details();
    musicName = "";
    fileUrl = "";
}

Music::Music(Details det)
{
    details = det;
    musicName = "";
    fileUrl = "";
}

void Music::setMusicName(QString musicName) {
    this->musicName = musicName;
}

void Music::setfileUrl(QString fileUrl) {
    this->fileUrl = fileUrl;
}

void Music::setDetail(Details details) {
    this->details = details;
}

QString Music::getMusicName() {
    return musicName;
}

QString Music::getFileUrl() {
    return fileUrl;
}

Details &Music::getDetails() {
    return details;
}
