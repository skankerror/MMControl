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

void OscCue::moveOscSendPrev(int row) // row pointeur dans v_listOscSend
{ // vérifier ?
  if (row < 1 || row > oscSendCount()) return;
  v_listOscSend.swapItemsAt(row -1, row);
}

void OscCue::executeCue() // peut-être inutile...
{
  for (int i = 0; i < v_listOscSend.size(); i++)
  {
    v_listOscSend.at(i)->ExecuteSend(); // TODO à voir ça de plus près
  }
}
