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
    Music(Details det);

    void setMusicName(QString musicName);
    void setfileUrl(QString fileUrl);
    void setDetail(Details details);

    QString getMusicName();
    QString getFileUrl();
    Details &getDetails();

private:
    QString musicName;
    QString fileUrl;
    Details details;
};

#endif // MUSIC_H
