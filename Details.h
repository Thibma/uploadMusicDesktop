#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QUrl>


class Details
{
public:
    Details();

    void setName(QString name);
    void setUrl(QString url);

    QString getName();
    QString getUrl();

private:
    QString name;
    QString urlImage;
};

#endif // AUTHOR_H
