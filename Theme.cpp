#include "Theme.h"

Theme::Theme(QString id, QString name)
{
    m_id = id;
    m_name = name;
}

QString Theme::getName()
{
    return m_name;
}

QString Theme::getId()
{
    return m_id;
}
