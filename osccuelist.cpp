#include "osccuelist.h"

OscCueList::OscCueList():
    QObject()
{

}

void OscCueList::addCue(OscCue *osccue)
{
    v_listCue.append(osccue);
}
