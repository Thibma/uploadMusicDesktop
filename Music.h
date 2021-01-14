#ifndef MUSIC_H
#define MUSIC_H

#include <QString>
#include <QUrl>

#include "Details.h"
#include "theme.h"


class Music
{
public:
    Music();

private:
    QString musicName;
    QUrl fileUrl;
    Details details;
    //Theme theme;
};

#endif // MUSIC_H
