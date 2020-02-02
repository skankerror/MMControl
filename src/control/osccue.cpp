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

OscSend* OscCue::getOscSend(int vectAt) const
{
  return v_listOscSend.at(vectAt);
}

void OscCue::addOscSend(OscSend *oscsend)
{
  v_listOscSend.append(oscsend);
  qDebug() << "Add oscsend ";
}

void OscCue::insertOscSend(int vectAt, OscSend *oscsend)
{
  if (vectAt > oscSendCount() - 1) return;
  v_listOscSend.insert(vectAt, oscsend);
}

void OscCue::removeOscSend(int vectAt)
{
  if (vectAt > oscSendCount() - 1 || vectAt < 0) return;
  v_listOscSend.remove(vectAt);
}

void OscCue::removeAllOscSend()
{
  qDeleteAll(v_listOscSend);
}

void OscCue::moveOscSendPrev(int vectAt) // row pointeur dans v_listOscSend
{ // vérifier ?
  if (vectAt < 1 || vectAt > oscSendCount() - 1) return;
  v_listOscSend.swapItemsAt(vectAt -1, vectAt);
}

//void OscCue::executeCue() // peut-être inutile...
//{
//  for (int i = 0; i < v_listOscSend.size(); i++)
//  {
//    v_listOscSend.at(i)->ExecuteSend(); // TODO à voir ça de plus près
//  }
//}
