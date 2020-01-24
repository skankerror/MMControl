#include "osccue.h"

OscCue::OscCue(QObject *parent) : QObject(parent)
{}

OscCue::~OscCue()
{
  qDeleteAll(v_listOscSend);
}

int OscCue::oscSendCount()
{
  return v_listOscSend.size();
}

OscSend *OscCue::getOscSend(int row) const
{
  return v_listOscSend.at(row);
}

void OscCue::addOscSend(OscSend *oscsend)
{
  v_listOscSend.append(oscsend);
}

void OscCue::insertOscSend(int row, OscSend *oscsend)
{
  v_listOscSend.insert(row, oscsend);
}

void OscCue::removeOscSend(int row)
{
  v_listOscSend.remove(row);
}

void OscCue::removeAllOscSend()
{
  qDeleteAll(v_listOscSend);
}

void OscCue::moveOscSendPrev(int row)
{
  v_listOscSend.swapItemsAt(row -1, row);
}

void OscCue::executeCue()
{
  for (int i = 0; i < v_listOscSend.size(); i++)
  {
    v_listOscSend.at(i)->ExecuteSend();
  }
}
