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

#include "oscsend.h"

OscSend::OscSend(QObject *parent,
                 champMM champ,
                 QString p_uri,
                 QString p_name,
                 QString p_name2,
                 QString p_color,
                 int p_ID1,
                 int p_ID2,
                 int p_rate,
                 int p_opacity,
                 int p_volume,
                 QString m_name,
                 QString m_name2,
                 int m_ID1,
                 int m_opacity,
                 bool m_isvisible,
                 bool m_issolo,
                 bool m_islocked,
                 int m_depth,
                 double time,
                 bool isfadein,
                 double waitTime,
                 QString noteSend):
  QObject(parent),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_p_uri(p_uri),
  m_p_name(p_name),
  m_p_name2(p_name2),
  m_p_color(p_color),
  m_p_ID1(p_ID1),
  m_p_ID2(p_ID2),
  m_p_rate(p_rate),
  m_p_opacity(p_opacity),
  m_p_volume(p_volume),
  m_m_name(m_name),
  m_m_name2(m_name2),
  m_m_ID1(m_ID1),
  m_m_opacity(m_opacity),
  m_m_isvisible(m_isvisible),
  m_m_issolo(m_issolo),
  m_m_islocked(m_islocked),
  m_m_depth(m_depth),
  m_time(time),
  m_isfadein(isfadein),
  m_timeWait(waitTime),
  m_noteSend(noteSend)
{
  timer = new QTimer();
  counter = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(fadeStep()));
}

OscSend::~OscSend()
{}

void OscSend::ExecuteSend()
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  packet << osc::BeginBundleImmediate;
  switch (m_champ)
  {
  case NOOP:
//    qDebug() << "Noop... wait " << m_time ;
    break;
  case PLAY: packet << osc::BeginMessage("/mapmap/play") << osc::EndMessage;
//    qDebug() << "/mapmap/play";
    break;
  case PAUSE: packet << osc::BeginMessage("/mapmap/pause") << osc::EndMessage;
//    qDebug() << "/mapmap/pause";
    break;
  case REWIND: packet << osc::BeginMessage("/mapmap/rewind") << osc::EndMessage;
//    qDebug() << "/mapmap/rewind";
    break;
  case QUIT: packet << osc::BeginMessage("/mapmap/quit") << osc::EndMessage;
//    qDebug() << "/mapmap/quit";
    break;
  case P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_ID1 << m_p_name.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/name is " << m_p_ID1 << " " << m_p_name.toStdString().c_str();
    break;
  case P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_ID1 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/rewind " << m_p_ID1 << " ";
    break;
  case P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_ID1 << ((float)m_p_opacity)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/opacity if " << m_p_ID1 << " " << ((float)m_p_opacity)/100;
    break;
  case P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_ID1 << ((float)m_p_volume)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/volume if " << m_p_ID1 << " " << ((float)m_p_volume)/100;
    break;
  case P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_ID1 << ((float)m_p_rate)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/rate if " << m_p_ID1 << " " << ((float)m_p_rate)/100;
    break;
  case P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_ID1 << m_p_uri.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/uri is " << m_p_ID1 << " " << m_p_uri.toStdString().c_str();
    break;
  case P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_ID1 << m_p_color.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/color is " << m_p_ID1 << m_p_color.toStdString().c_str();
    break;
  case M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_ID1 << m_m_name.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/name is " << m_m_ID1 << " " << m_m_name.toStdString().c_str();
    break;
  case M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_ID1 << ((float)m_m_opacity)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/opacity if " << m_m_ID1 << " " << ((float)m_m_opacity)/100;
    break;
  case M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_ID1 << m_m_isvisible << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/visible ii " << m_m_ID1 << m_m_isvisible;
    break;
  case M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_ID1 << m_m_issolo << osc::EndMessage;
//      qDebug() << "/mapmap/mapping/solo ii " << m_m_ID1 << " " << m_m_issolo;
    break;
  case M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_ID1 << m_m_islocked << osc::EndMessage;
//      qDebug() << "/mapmap/mapping/locked ii " << m_m_ID1 << " " << m_m_islocked;
    break;
  case M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_ID1 << m_m_depth << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/depth ii " << m_m_ID1 << " " << m_m_depth;
    break;
  case P_XFADE: ExecuteXFade(m_p_ID1, m_p_ID2, m_time); break;
  case P_FADE: ExecuteFade(m_p_ID1, m_time, m_isfadein); break;
  case R_P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_name.toStdString().c_str() << m_p_name2.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/name ss " << m_p_name.toStdString().c_str() << " " << m_p_name2.toStdString().c_str();
    break;
  case R_P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_name.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/rewind s " << m_p_name.toStdString().c_str();
    break;
  case R_P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_name.toStdString().c_str() << ((float)m_p_opacity)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/opacity sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_opacity)/100;
    break;
  case R_P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_name.toStdString().c_str() << ((float)m_p_volume)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/volume sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_volume)/100;
    break;
  case R_P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_name.toStdString().c_str() << ((float)m_p_rate)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/paint/rate sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_rate)/100;
    break;
  case R_P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_name.toStdString().c_str() << m_p_uri.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/uri ss " << m_p_name.toStdString().c_str() << " " << m_p_uri.toStdString().c_str() ;
    break;
  case R_P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_name.toStdString().c_str() << m_p_color.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/paint/color ss " << m_p_name.toStdString().c_str() << " " << m_p_color.toStdString().c_str() ;
    break;
  case R_M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_name.toStdString().c_str() << m_m_name2.toStdString().c_str() << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/name ss " << m_m_name.toStdString().c_str() << " " << m_m_name2.toStdString().c_str() ;
    break;
  case R_M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_name.toStdString().c_str() << ((float)m_m_opacity)/100 << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/opacity sf " << m_m_name.toStdString().c_str() << " " << ((float)m_m_opacity)/100;
    break;
  case R_M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_name.toStdString().c_str() << m_m_isvisible << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/visible si " << m_m_name.toStdString().c_str() << m_m_isvisible;
    break;
  case R_M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_name.toStdString().c_str() << m_m_issolo << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/solo si " << m_m_name.toStdString().c_str() << " " << m_m_issolo;
    break;
  case R_M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_name.toStdString().c_str() << m_m_islocked << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/locked si " << m_m_name.toStdString().c_str() << " " << m_m_islocked;
    break;
  case R_M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_name.toStdString().c_str() << m_m_depth << osc::EndMessage;
//    qDebug() << "/mapmap/mapping/depth si " << m_m_name.toStdString().c_str() << " " << m_m_depth;
    break;
  case R_P_FADE: ExecutePFade(m_p_name, m_time, m_isfadein); break;
  case R_P_XFADE: ExecutePXFade(m_p_name, m_p_name2, m_time); break;
  default: packet << osc::BeginMessage("/error_default_champ") << osc::EndMessage;
    qDebug() << "/sa/pa/normal error execute send";
    break;
  }
  packet << osc::EndBundle;
  Send(packet.Data(), packet.Size());
}

void OscSend::ExecuteXFade(int ID1, int ID2, double time)
{
  if (counter == 101) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / 100;
  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity")
         << ID1 << 1 - i << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();

  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity")
         << ID2 << i << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();
  timer->start(time * 10);
}

void OscSend::ExecuteFade(int ID1, double time, bool isfadein)
{
  if (counter == 101) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / 100;
  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity") << ID1;
  if (isfadein) packet << i;
    else packet << 1 - i;
    packet << osc::EndMessage << osc::EndBundle;
    Send(packet.Data(), packet.Size());
    packet.Clear();
    timer->start(time * 10);

}

void OscSend::ExecutePXFade(const QString &p_name, const QString &p_name2, double time)
{
  if (counter == 101) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / 100;
  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity")
         << p_name.toStdString().c_str() << 1 - i << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();

  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity")
         << p_name2.toStdString().c_str() << i << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();
  timer->start(time * 10);
}

void OscSend::ExecutePFade(const QString &p_name, double time, bool isfadein)
{
  if (counter == 101) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / 100;

  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity") << p_name.toStdString().c_str();
  if (isfadein)
    packet << i;
  else
    packet << 1 - i;
  packet << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();
  timer->start(time * 10);
}

void OscSend::fadeStep()
{
  if (counter == 101)
  {
    fadeFinish();
    return;
  }
  counter++;
  ExecuteSend();
}

void OscSend::fadeFinish()
{
  if (timer->isActive())
  {
    timer->stop();
    counter = 0;
    return;
  }
  counter = 0;
}

QString OscSend::getChampToString(int champ)
{
  switch(champ)
  {
  case NOOP: return QString("NOOP"); break;
  case PLAY: return QString("PLAY"); break;
  case PAUSE: return QString("PAUSE"); break;
  case REWIND: return QString("REWIND"); break;
  case QUIT: return QString("QUIT"); break;
  case P_NAME: return QString("P_NAME"); break;
  case P_REWIND: return QString("P_REWIND"); break;
  case P_OPACITY: return QString("P_OPACITY"); break;
  case P_VOLUME: return QString("P_VOLUME"); break;
  case P_RATE: return QString("P_RATE"); break;
  case P_URI: return QString("P_URI"); break;
  case P_COLOR: return QString("P_COLOR"); break;
  case M_NAME: return QString("M_NAME"); break;
  case M_OPACITY: return QString("M_OPACITY"); break;
  case M_VISIBLE: return QString("M_VISIBLE"); break;
  case M_SOLO: return QString("M_SOLO"); break;
  case M_LOCK: return QString("M_LOCK"); break;
  case M_DEPTH: return QString("M_DEPTH"); break;
  case P_XFADE: return QString("P_XFADE"); break;
  case P_FADE: return QString("P_FADE"); break;
  case R_P_NAME: return QString("R_P_NAME"); break;
  case R_P_REWIND: return QString("R_P_REWIND"); break;
  case R_P_OPACITY: return QString("R_P_OPACITY"); break;
  case R_P_VOLUME: return QString("R_P_VOLUME"); break;
  case R_P_RATE: return QString("R_P_RATE"); break;
  case R_P_URI: return QString("R_P_URI"); break;
  case R_P_COLOR: return QString("R_P_COLOR"); break;
  case R_M_NAME: return QString("R_M_NAME"); break;
  case R_M_OPACITY: return QString("R_M_OPACITY"); break;
  case R_M_VISIBLE: return QString("R_M_VISIBLE"); break;
  case R_M_SOLO: return QString("R_M_SOLO"); break;
  case R_M_LOCK: return QString("R_M_LOCK"); break;
  case R_M_DEPTH: return QString("R_M_DEPTH"); break;
  case R_P_FADE: return QString("R_P_FADE"); break;
  case R_P_XFADE: return QString("R_P_XFADE"); break;
  default:
    qDebug() << "error OscSend::getChampToString(arg)" << champ << "badly returned";
    return QString(""); break;
  }
}

int OscSend::getChampFromString(const QString &value)
{
  if (value == "NOOP") return NOOP;
  if (value == "PLAY") return PLAY;
  if (value == "PAUSE") return PAUSE;
  if (value == "REWIND") return REWIND;
  if (value == "QUIT") return QUIT;
  if (value == "P_NAME") return P_NAME;
  if (value == "P_REWIND") return P_REWIND;
  if (value == "P_OPACITY") return P_OPACITY;
  if (value == "P_VOLUME") return P_VOLUME;
  if (value == "P_RATE") return P_RATE;
  if (value == "P_URI") return P_URI;
  if (value == "P_COLOR") return P_COLOR;
  if (value == "M_NAME") return M_NAME;
  if (value == "M_OPACITY") return M_OPACITY;
  if (value == "M_VISIBLE") return M_VISIBLE;
  if (value == "M_SOLO") return M_SOLO;
  if (value == "M_LOCK") return M_LOCK;
  if (value == "M_DEPTH") return M_DEPTH;
  if (value == "P_XFADE") return P_XFADE;
  if (value == "P_FADE") return P_FADE;
  if (value == "R_P_NAME") return R_P_NAME;
  if (value == "R_P_REWIND") return R_P_REWIND;
  if (value == "R_P_OPACITY") return R_P_OPACITY;
  if (value == "R_P_VOLUME") return R_P_VOLUME;
  if (value == "R_P_RATE") return R_P_RATE;
  if (value == "R_P_URI") return R_P_URI;
  if (value == "R_P_COLOR") return R_P_COLOR;
  if (value == "R_M_NAME") return R_M_NAME;
  if (value == "R_M_OPACITY") return R_M_OPACITY;
  if (value == "R_M_VISIBLE") return R_M_VISIBLE;
  if (value == "R_M_SOLO") return R_M_SOLO;
  if (value == "R_M_LOCK") return R_M_LOCK;
  if (value == "R_M_DEPTH") return R_M_DEPTH;
  if (value == "R_P_FADE") return R_P_FADE;
  if (value == "R_P_XFADE") return R_P_XFADE;
  qDebug() << "error OscSend::getChampFromString returned -1";
  return -1;
}
