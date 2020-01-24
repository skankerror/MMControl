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
#include <QDebug>
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

  Q_ENUM(champMM)

  OscSend(QObject *parent = nullptr,
          champMM champ = NOOP,
          QString p_uri = "",
          QString p_name = "",
          QString p_name2 = "",
          QString p_color = "",
          int p_ID1 = 0,
          int p_ID2 = 0,
          int p_rate = 0,
          int p_opacity = 0,
          int p_volume = 0,
          QString m_name = "",
          QString m_name2 = "",
          int m_ID1 = 0,
          int m_opacity = 0,
          bool m_isvisible = false,
          bool m_issolo = false,
          bool m_islocked = false,
          int m_depth = 0,
          double time = 0,
          bool isfadein = false,
          double waitTime = 0);

  void ExecuteSend();
  void ExecuteXFade(int ID1, int ID2, double time);
  void ExecuteFade(int ID1, double time, bool isfadein);
  void ExecutePXFade(QString p_name1, QString p_name2, double time);
  void ExecutePFade(QString p_name, double time, bool isfadein);

  champMM m_champ;
  // paint var
  QString m_p_uri = "";
  QString m_p_name = "";
  QString m_p_name2 = ""; // pour R_P_NAME, R_P_XFADE
  QString m_p_color = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0; // pour P_XFade
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;
  // mapping var
  QString m_m_name = "";
  QString m_m_name2 = ""; // pour R_M_NAME
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  int m_m_depth = 0;
  // general var
  double m_time = 0;
  bool m_isfadein = false; // pour P_FADE
  double m_timeWait = 0; // pour savoir si la cue doit s'enchaîner
};

#endif // OSCSEND_H
