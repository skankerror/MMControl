/*
 * (c) 2020 Michaël Creusy -- creusy(.)michael(@)gmail(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "osccue.h"

OscCue::OscCue(QObject *parent, double totalTime, QString noteCue) :
  QObject(parent),
  m_totalTime(totalTime),
  m_noteCue(noteCue)
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
  // update total time de la cue
  int champ = oscsend->getChamp();
  if (champ == P_XFADE || champ == R_P_XFADE || champ == P_FADE || champ == R_P_FADE)
    m_totalTime += oscsend->getTime();
  m_totalTime += oscsend->getTimewait();
//  qDebug() << "OscCue::addOscSend success, new size for cue :" << oscSendCount()
//           << "totalTime =" << m_totalTime;
}

void OscCue::insertOscSend(int vectAt, OscSend *oscsend)
{
  if (vectAt < 0 || vectAt > oscSendCount()/* - 1*/) return;
  v_listOscSend.insert(vectAt, oscsend);
  // update total time de la cue
  int champ = oscsend->getChamp();
  if (champ == P_XFADE || champ == R_P_XFADE || champ == P_FADE || champ == R_P_FADE)
    m_totalTime += oscsend->getTime();
  m_totalTime += oscsend->getTimewait();
//  qDebug() << "OscCue::insertOscSend success, new size fur cue :" << oscSendCount()
//           << "totalTime =" << m_totalTime;
}

void OscCue::removeOscSend(int vectAt)
{
  if (vectAt > oscSendCount() - 1 || vectAt < 0) return;
  // On choppe l'oscsend avant pour lui enlever son time du total
  OscSend *oscsend = getOscSend(vectAt);
  // update total time de la cue
  int champ = oscsend->getChamp();
  if (champ == P_XFADE || champ == R_P_XFADE || champ == P_FADE || champ == R_P_FADE)
      m_totalTime -= oscsend->getTime();
    m_totalTime -= oscsend->getTimewait();
    v_listOscSend.remove(vectAt);
//  qDebug() << "OscCue::removeOscSend success at" << vectAt << "new size fur cue :" << oscSendCount()
//           << "totalTime =" << m_totalTime;
}

void OscCue::removeAllOscSend()
{
  qDeleteAll(v_listOscSend);
  m_totalTime = 0;
//  qDebug() << "OscCue::removeAllOscSend success, new size fur cue :" << oscSendCount();
}

void OscCue::moveOscSendPrev(int vectAt) // row pointeur dans v_listOscSend
{ // vérifier ?
  if (vectAt < 1 || vectAt > oscSendCount() - 1) return;
  v_listOscSend.swapItemsAt(vectAt -1, vectAt);
//  qDebug() << "OscCue::moveOscSendPrev success, swap :" << vectAt - 1 << vectAt;
}

