#include "osccue.h"

OscCue::OscCue(QObject *parent) : QObject(parent)
{}

OscCue::~OscCue()
{
  qDeleteAll(v_listOscSend);
}

int OscCue::oscSendCount() const
{
//  qDebug() << "OscCue::oscSendCount returns :" << v_listOscSend.size();
  return v_listOscSend.size();
}

OscSend* OscCue::getOscSend(int vectAt)
{
  if (vectAt < 0 || vectAt > oscSendCount() - 1)
  {
    OscSend *emptySend = new OscSend(this, NOOP);
    qDebug() << "getOscSend badly returned";
    return emptySend;
  }
  return v_listOscSend.at(vectAt);
}

void OscCue::addOscSend(OscSend *oscsend)
{
  v_listOscSend.append(oscsend);
  qDebug() << "OscCue::addOscSend success, new size for cue :" << oscSendCount();
}

void OscCue::insertOscSend(int vectAt, OscSend *oscsend)
{
  if (vectAt < 0 || vectAt > oscSendCount()/* - 1*/) return;
  v_listOscSend.insert(vectAt, oscsend);
  qDebug() << "OscCue::insertOscSend success, new size fur cue :" << oscSendCount();
}

void OscCue::removeOscSend(int vectAt)
{
  if (vectAt > oscSendCount() - 1 || vectAt < 0) return;
  v_listOscSend.remove(vectAt);
  qDebug() << "OscCue::removeOscSend success at" << vectAt << "new size fur cue :" << oscSendCount();
}

void OscCue::removeAllOscSend()
{
  qDeleteAll(v_listOscSend);
  qDebug() << "OscCue::removeAllOscSend success, new size fur cue :" << oscSendCount();
}

void OscCue::moveOscSendPrev(int vectAt) // row pointeur dans v_listOscSend
{ // vérifier ?
  if (vectAt < 1 || vectAt > oscSendCount() - 1) return;
  v_listOscSend.swapItemsAt(vectAt -1, vectAt);
  qDebug() << "OscCue::moveOscSendPrev success, swap :" << vectAt - 1 << vectAt;
}

