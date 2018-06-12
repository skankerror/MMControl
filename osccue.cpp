#include "osccue.h"

OscCue::OscCue() :
    //QObject(),
    QStandardItemModel(1, 17)
{
    QStringList Headers;
    Headers << "EventName" << "champ"
                     << "p_ID1" << "p_ID2" << "p_uri"
                     << "p_color" << "p_rate"
                     << "p_opacity" << "p_volume"
                     << "m_ID" << "m_opacity"
                     << "m_visible" "m_solo"
                     << "m_lock" << "m_depth"
                     << "time" << "fade in";
    setHorizontalHeaderLabels(Headers);
}
OscCue::OscCue(OscSend *oscsend) :
    //QObject(),
    QStandardItemModel(1, 17)
{
    QStringList Headers;
    Headers << "EventName" << "champ"
                     << "p_ID1" << "p_ID2" << "p_uri"
                     << "p_color" << "p_rate"
                     << "p_opacity" << "p_volume"
                     << "m_ID" << "m_opacity"
                     << "m_visible" "m_solo"
                     << "m_lock" << "m_depth"
                     << "time" << "fade in";
    setHorizontalHeaderLabels(Headers);
    setItem(0, 0, oscsend);
}
