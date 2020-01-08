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
  OscSend(champMM champ, int time = 0); // 0, 1, 2, 3, 4
  OscSend(champMM champ, int ID1, QString name,
          int time = 0); // 5, 10, 11, 12;
  OscSend(champMM champ, int p_ID1, int time); // 6
  OscSend(champMM champ, int ID1, int var,
          int time); // 7, 8, 9, 13, 17, 18; gros bordel !
  OscSend(champMM champ, int ID1, bool isproperty,
          int time = 0); // 14 15 16 19

  // Faire constructeur pour regexp

  void ExecuteSend();
  void ExecuteXFade(int ID1, int ID2, int time);
  void ExecuteFade(int ID1, int time, bool isfadein);

  champMM m_champ;

  QString m_p_uri = "";
  QString m_p_name = "";
  QString m_p_color = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0; // pour boucle...
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;

  QString m_m_name = "";
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  int m_m_depth = 0;

  int m_time = 0;
  bool m_isfadein = false;
  bool m_iswaiting = true;
};

#endif // OSCSEND_H
