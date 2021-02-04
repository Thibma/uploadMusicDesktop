#ifndef THEME_H
#define THEME_H

#include <QString>


class Theme
{
public:
    Theme(QString id, QString name);
    QString getName();
    QString getId();

private:
    QString m_name;
    QString m_id;
};

#endif // THEME_H
