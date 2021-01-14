#ifndef THEME_H
#define THEME_H

#include <QString>


class Theme
{
public:
    Theme(QString name);
    QString getName();

private:
    QString m_name;
};

#endif // THEME_H
