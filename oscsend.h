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

#ifndef OSCSEND_H
#define OSCSEND_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QColor>
#include <iostream>
#include <unistd.h>
#include "contrib/oscpack/osc/OscOutboundPacketStream.h"
#include "contrib/oscpack/ip/UdpSocket.h"
#include "contrib/oscpack/ip/NetworkingUtils.h"
#include "contrib/oscpack/ip/IpEndpointName.h"
#include "MMC.h"

class OscSend : public QObject,
    public UdpTransmitSocket
{
  Q_OBJECT
public:
  // cstr 1: 0 NOOP, 1 PLAY, 2 PAUSE, 3 REWIND, 4 QUIT
  OscSend(champMM champ, int time = 0);
  // cstr 2: 5 P_NAME, 10 P_URI, 11 P_COLOR, 12 M_NAME, 22 R_P_OPACITY, 23 R_P_VOLUME,
  // 24 R_P_RATE, 28 R_M_OPACITY, 32 R_M_DEPTH
  OscSend(champMM champ, int unInt, QString name, int time = 0);
  // cstr 3: 6 P_REWIND
  OscSend(champMM champ, int p_ID1, int time);
  // cstr 4: 7 P_OPACITY, 8 P_VOLUME, 9 P_RATE, 13 M_OPACITY, 17 M_DEPTH, 18 P_XFADE
  OscSend(champMM champ, int ID1, int var, int time);
  // cstr 5: 14 M_VISIBLE, 15 M_SOLO, 16 M_LOCK, 19 P_FADE
  OscSend(champMM champ, int ID1, bool isproperty, int time = 0);
  // cstr 6 : 21 R_P_REWIND
  OscSend(champMM champ, QString name, int time = 0);
  // cstr 7 : 20 R_P_NAME, 25 R_P_URI, 26 R_P_COLOR, 27 R_M_NAME, 34 R_P_XFADE
  OscSend(champMM champ, QString name1, QString name2, int time = 0);
  // CSTR 8 : 29 R_M_VISIBLE, 30 R_M_SOLO, 31 R_M_LOCK, 33 R_P_FADE
  OscSend(champMM champ, QString name, bool isproperty, int time = 0);

  void ExecuteSend();
  void ExecuteXFade(int ID1, int ID2, int time);
  void ExecuteFade(int ID1, int time, bool isfadein);
  void ExecutePXFade(QString p_name1, QString p_name2, int time);
  void ExecutePFade(QString p_name, int time, bool isfadein);

  champMM m_champ;

  QString m_p_uri = "";
  QString m_p_name = "";
  QString m_p_name2 = ""; // pour R_P_NAME, R_P_XFADE
  QString m_p_color = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0; // pour P_XFade
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;

  QString m_m_name = "";
  QString m_m_name2 = ""; // pour R_M_NAME
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  int m_m_depth = 0;

  int m_time = 0;
  bool m_isfadein = false; // pour P_FADE
  bool m_iswaiting = true; // pour savoir si la cue doit s'enchaîner
};

#endif // OSCSEND_H
