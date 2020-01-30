#include "osccue.h"

OscCue::OscCue(QObject *parent) : QObject(parent)
{}

OscCue::~OscCue()
{
  qDeleteAll(v_listOscSend);
}

void OscCue::addOscSend(OscSend *oscsend)
{
  v_listOscSend.append(oscsend);
  qDebug() << "Add oscsend ";
}

void OscCue::executeCue()
{
  for (int i = 0; i < v_listOscSend.size(); i++)
  {
    v_listOscSend.at(i)->ExecuteSend(); // TODO à voir ça de plus près
  }
}
