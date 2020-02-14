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
#include <QFile>
#include <QColor>
#include <QDebug>
#include <QTimer>
#include "contrib/oscpack/osc/OscOutboundPacketStream.h"
#include "contrib/oscpack/ip/UdpSocket.h"
#include "contrib/oscpack/ip/NetworkingUtils.h"
#include "contrib/oscpack/ip/IpEndpointName.h"
#include "MMC.h"


class OscSend :
    public QObject,
    public UdpTransmitSocket
{
  Q_OBJECT

public:

  OscSend(QObject *parent = nullptr,
          champMM champ = CUE,
          OscSend *parentSend = nullptr,
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
          double waitTime = 0,
          QString noteSend = "");
  OscSend(OscSend *oscsend); // cstr de copie
  ~OscSend();

signals:
  void executeSendFinished();
  void sendStringToOutputLabel(QString);

public slots:

  void ExecuteSend();
  void ExecuteXFade(int ID1, int ID2, double time);
  void ExecuteFade(int ID1, double time, bool isfadein);
  void ExecutePXFade(const QString &p_name1, const QString &p_name2, double time);
  void ExecutePFade(const QString &p_name, double time, bool isfadein);
  void fadeStep();
  void fadeFinish();


public:
  //Getters
  champMM getChamp() const { return m_champ; };
  static QString getChampToString(int champ);
  static int getChampFromString(const QString &value);
  QString getP_uri() const { return m_p_uri; };
  QString getP_name() const { return m_p_name; };
  QString getP_name2() const{ return m_p_name2; };
  QString getP_color() const{ return m_p_color; };
  int getP_ID1() const{ return m_p_ID1; };
  int getP_ID2() const{ return m_p_ID2; };
  int getP_rate() const{ return m_p_rate; };
  int getP_opacity() const{ return m_p_opacity; };
  int getP_volume() const{ return m_p_volume; };
  QString getM_name() const{ return m_m_name; };
  QString getM_name2() const{ return m_m_name2; };
  int getM_ID1() const{ return m_m_ID1; };
  int getM_opacity() const{ return m_m_opacity;};
  bool getM_isvisible() const{ return m_m_isvisible; };
  bool getM_issolo() const{ return m_m_issolo; };
  bool getM_islocked() const{ return m_m_islocked; };
  int getM_depth() const{ return m_m_depth; };
  double getTime() const{ return m_time; };
  bool getIsfadein() const{ return m_isfadein; };
  double getTimewait() const{ return m_timeWait; };
  QString getNoteSend() const{ return m_noteSend; };

  //Setters
  void setChamp(champMM champ){ m_champ = champ; };
  void setP_uri(QString p_uri){ m_p_uri = p_uri; };
  void setP_name(QString p_name){ m_p_name = p_name; };
  void setP_name2(QString p_name2){ m_p_name2 = p_name2; };
  void setP_color(QString p_color){ m_p_color = p_color; };
  void setP_ID1(int p_ID1){ m_p_ID1 = p_ID1; };
  void setP_ID2(int p_ID2){ m_p_ID2 = p_ID2; };
  void setP_rate(int p_rate){ m_p_rate = p_rate; };
  void setP_opacity(int p_opacity){ m_p_opacity = p_opacity; };
  void setP_volume(int p_volume){ m_p_volume = p_volume; };
  void setM_name(QString m_name){ m_m_name = m_name; };
  void setM_name2(QString m_name2){ m_m_name2 = m_name2; };
  void setM_ID1(int m_ID1){ m_m_ID1 = m_ID1; };
  void setM_opacity(int m_opacity){ m_m_opacity = m_opacity; };
  void setM_isvisible(bool m_isvisible){ m_m_isvisible = m_isvisible; };
  void setM_issolo(bool m_issolo){ m_m_issolo = m_issolo; };
  void setM_islocked(bool m_islocked){ m_m_islocked = m_islocked; };
  void setM_depth(int m_depth){ m_m_depth = m_depth; };
  void setTime(double time){ m_time = time; };
  void setIsfadein(bool isfadein){ m_isfadein = isfadein; };
  void setTimewait(double timewait){ m_timeWait = timewait; };
  void setNoteSend(QString noteSend){ m_noteSend = noteSend; };
  void setParentSend(OscSend *osccue);

  OscSend *getChild(int position);
  int getSendCount() const;
  void insertSend(OscSend *oscsend, int position);
  OscSend *getParentSend();
  void removeSends(int position, int count = 1);
  int getSendId() const; // donne l'id d'un enfant
  void moveChildPrev(int position);

private:
  champMM m_champ = CUE;
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
  double m_timeWait = 0;
  QString m_noteSend = "";

  QTimer *timer;
  int counter = 0; // pour fonctionner avec le time
  int timeRes = 100;

  QVector<OscSend *> v_listSend; // Si c'est une cue
  OscSend *m_parentSend; // rootItem si c'est une cue
};

#endif // OSCSEND_H
