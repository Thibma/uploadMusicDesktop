#include "Theme.h"

Theme::Theme(QString name)
{
    m_name = name;
}

QString Theme::getName()
{
    return m_name;
}
