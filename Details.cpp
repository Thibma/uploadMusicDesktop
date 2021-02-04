#include "Details.h"

Details::Details()
{
    name = "";
    urlImage = "";
}

void Details::setName(QString name) {
    this->name = name;
}

void Details::setUrl(QString url) {
    this->urlImage = url;
}

QString Details::getName() {
    return name;
}

QString Details::getUrl() {
    return urlImage;
}
