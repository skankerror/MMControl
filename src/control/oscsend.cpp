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
                 OscSend *parentSend,
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
  m_noteSend(noteSend),
  m_parentSend(parentSend)

{
  timer = new QTimer();
  counter = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(fadeStep()));
}

OscSend::OscSend(OscSend *oscsend):
  QObject(nullptr),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(oscsend->getChamp()),
  m_p_uri(oscsend->getP_uri()),
  m_p_name(oscsend->getP_name()),
  m_p_name2(oscsend->getP_name2()),
  m_p_color(oscsend->getP_color()),
  m_p_ID1(oscsend->getP_ID1()),
  m_p_ID2(oscsend->getP_ID2()),
  m_p_rate(oscsend->getP_rate()),
  m_p_opacity(oscsend->getP_opacity()),
  m_p_volume(oscsend->getP_volume()),
  m_m_name(oscsend->getM_name()),
  m_m_name2(oscsend->getM_name2()),
  m_m_ID1(oscsend->getM_ID1()),
  m_m_opacity(oscsend->getM_opacity()),
  m_m_isvisible(oscsend->getM_isvisible()),
  m_m_issolo(oscsend->getM_issolo()),
  m_m_islocked(oscsend->getM_islocked()),
  m_m_depth(oscsend->getM_depth()),
  m_time(oscsend->getTime()),
  m_isfadein(oscsend->getIsfadein()),
  m_timeWait(oscsend->getTimewait()),
  m_noteSend(oscsend->getNoteSend()),
  m_parentSend(nullptr)

{
  timer = new QTimer();
  counter = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(fadeStep()));
}


OscSend::~OscSend()
{
  qDeleteAll(v_listSend);
}

void OscSend::execute()
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  packet << osc::BeginBundleImmediate;
  switch (m_champ)
  {
  case PLAY: packet << osc::BeginMessage("/mapmap/play") << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel("/mapmap/play");
    break;
  case PAUSE: packet << osc::BeginMessage("/mapmap/pause") << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel("/mapmap/pause");
    break;
  case REWIND: packet << osc::BeginMessage("/mapmap/rewind") << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel("/mapmap/rewind");
    break;
  case QUIT: packet << osc::BeginMessage("/mapmap/quit") << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel("/mapmap/quit");
    break;
  case P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_ID1 << m_p_name.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("mapmap/paint/name %1 ").arg(m_p_ID1).append(m_p_name));
    break;
  case P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_ID1 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/rewind %1").arg(m_p_ID1));
    break;
  case P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_ID1 << ((float)m_p_opacity)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/opacity %1 %2").arg(m_p_ID1).arg(m_p_opacity));
    break;
  case P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_ID1 << ((float)m_p_volume)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/volume %1 %2").arg(m_p_ID1).arg(m_p_volume));
    break;
  case P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_ID1 << ((float)m_p_rate)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/rate %1 %2").arg(m_p_ID1).arg(m_p_volume));
    break;
  case P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_ID1 << m_p_uri.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/uri %1 ").arg(m_p_ID1).append(m_p_uri));
    break;
  case P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_ID1 << m_p_color.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/color %1 ").arg(m_p_ID1).append(m_p_color));
    break;
  case M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_ID1 << m_m_name.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/name %1 ").arg(m_m_ID1).append(m_m_name));
    break;
  case M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_ID1 << ((float)m_m_opacity)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/opacity %1 %2").arg(m_m_ID1).arg(m_m_opacity));
    break;
  case M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_ID1 << m_m_isvisible << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/visible %1 %2").arg(m_m_ID1).arg(m_m_isvisible));
    break;
  case M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_ID1 << m_m_issolo << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/solo %1 %2").arg(m_m_ID1).arg(m_m_issolo));
    break;
  case M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_ID1 << m_m_islocked << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/locked %1 %2").arg(m_m_ID1).arg(m_m_islocked));
    break;
  case M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_ID1 << m_m_depth << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/depth %1 %2").arg(m_m_ID1).arg(m_m_depth));
    break;
  case P_XFADE: ExecuteXFade(m_p_ID1, m_p_ID2, m_time); break;
  case P_FADE: ExecuteFade(m_p_ID1, m_time, m_isfadein); break;
  case R_P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_name.toStdString().c_str() << m_p_name2.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/name ").append(m_p_name).append(" ").append(m_p_name2));
    break;
  case R_P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_name.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/rewind ").append(m_p_name));
    break;
  case R_P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_name.toStdString().c_str() << ((float)m_p_opacity)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/opacity ").append(m_p_name).append(" %1").arg(m_p_opacity));
    break;
  case R_P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_name.toStdString().c_str() << ((float)m_p_volume)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/volume ").append(m_p_name).append(" %1").arg(m_p_volume));
    break;
  case R_P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_name.toStdString().c_str() << ((float)m_p_rate)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/rate ").append(m_p_name).append(" %1").arg(m_p_rate));
    break;
  case R_P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_name.toStdString().c_str() << m_p_uri.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/uri ").append(m_p_name).append(" ").append(m_p_uri));
    break;
  case R_P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_name.toStdString().c_str() << m_p_color.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/paint/color ").append(m_p_name).append(" ").append(m_p_color));
    break;
  case R_M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_name.toStdString().c_str() << m_m_name2.toStdString().c_str() << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/name ").append(m_m_name).append(" ").append(m_m_name2));
    break;
  case R_M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_name.toStdString().c_str() << ((float)m_m_opacity)/100 << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/opacity ").append(m_m_name).append(" %1").arg(m_m_opacity));
    break;
  case R_M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_name.toStdString().c_str() << m_m_isvisible << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/visible ").append(m_m_name).append(" %1").arg(m_m_isvisible));
    break;
  case R_M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_name.toStdString().c_str() << m_m_issolo << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/solo ").append(m_m_name).append(" %1").arg(m_m_issolo));
    break;
  case R_M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_name.toStdString().c_str() << m_m_islocked << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/locked ").append(m_m_name).append(" %1").arg(m_m_islocked));
    break;
  case R_M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_name.toStdString().c_str() << m_m_depth << osc::EndMessage;
    emit executeSendFinished();
    emit sendStringToOutputLabel(QString("/mapmap/mapping/depth ").append(m_m_name).append(" %1").arg(m_m_depth));
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

void OscSend::ExecuteXFade(int ID1, int ID2, double time) // A voir de près pour le timeRes
{
  timeRes = (int)(100 * time); // on adapte la résolution suivant le temps
  if (counter == timeRes + 1) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / timeRes;
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
  emit sendStringToOutputLabel(QString("paint ID%1 -> %2\%   ***   paint ID%3 -> %4\%").
                               arg(ID1).arg((int)((1 - i) * 100)).arg(ID2).arg((int)(i * 100)));
  timer->start(10); // la résolution est fixe à 10ms
}

void OscSend::ExecuteFade(int ID1, double time, bool isfadein)
{
  timeRes = (int)(100 * time); // on adapte la résolution suivant le temps
  if (counter == timeRes + 1) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / timeRes;
  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity") << ID1;
  if (isfadein)
  {
    packet << i;
    emit sendStringToOutputLabel(QString("paint ID%1 -> %2\%").arg(ID1).arg((int)(i * 100)));
  }
  else
  {
    packet << 1 - i;
    emit sendStringToOutputLabel(QString("paint ID%1 -> %2\%").arg(ID1).arg((int)((1 - i) * 100)));
  }
  packet << osc::EndMessage << osc::EndBundle;
    Send(packet.Data(), packet.Size());
    packet.Clear();
    timer->start(10);
}

void OscSend::ExecutePXFade(const QString &p_name, const QString &p_name2, double time)
{
  timeRes = (int)(100 * time); // on adapte la résolution suivant le temps
  if (counter == timeRes + 1) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / timeRes;
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
  emit sendStringToOutputLabel(QString(p_name).append(" -> %1\%   ******   ").arg((int)((1 - i) * 100))
                               .append(p_name2).append(" -> %1\%").arg((int)(i * 100)));
  timer->start(10); // la résolution est fixe à 10ms
}

void OscSend::ExecutePFade(const QString &p_name, double time, bool isfadein)
{
  timeRes = (int)(100 * time); // on adapte la résolution suivant le temps
  if (counter == timeRes + 1) return;
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  double i = (double)(counter) / timeRes;
  packet << osc::BeginBundleImmediate
         << osc::BeginMessage("/mapmap/paint/opacity") << p_name.toStdString().c_str();
  if (isfadein)
  {
    packet << i;
    emit sendStringToOutputLabel(QString(p_name).append(" -> %1\%").arg((int)(i * 100)));
  }
  else
  {
    packet << 1 - i;
    emit sendStringToOutputLabel(QString(p_name).append(" -> %1\%").arg((int)((1 - i) * 100)));
  }
  packet << osc::EndMessage << osc::EndBundle;
  Send(packet.Data(), packet.Size());
  packet.Clear();
  timer->start(10);
}

void OscSend::fadeStep()
{
  if (counter == timeRes + 1)
  {
    fadeFinish();
    return;
  }
  counter++;
  execute();
}

void OscSend::fadeFinish()
{
  if (timer->isActive())
  {
    timer->stop();
    counter = 0;
    emit executeSendFinished();
    return;
  }
  emit executeSendFinished();
  counter = 0;
}

QString OscSend::getChampToString(const int champ)
{
  switch(champ)
  {
  case CUE: return QString("CUE"); break;
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
  if (value == "CUE") return CUE;
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

void OscSend::setParentSend(OscSend *osccue)
{
  m_parentSend = osccue;
}

OscSend *OscSend::getChild(const int position) const
{
  if (position < 0 || position >= v_listSend.size())
    return nullptr;
  return v_listSend.at(position);
}

int OscSend::getSendCount() const
{
  return v_listSend.count();
}

void OscSend::insertSend(OscSend *oscsend, const int position)
{
  if (position < 0 || position > v_listSend.size()) return;
  oscsend->setParentSend(this);
  v_listSend.insert(position, oscsend);
  m_timeWait += oscsend->getTimewait(); // on ajoute le timewait de la send que l'on vient d'insérer
  int champ = oscsend->getChamp();
  // Si c'est un fade on ajoute aussi le time
  if (champ == P_FADE || champ == P_XFADE || champ == R_P_FADE || champ == R_P_XFADE) m_timeWait += oscsend->getTime();
}

OscSend *OscSend::getParentSend() const
{
  return m_parentSend;
}

void OscSend::removeSends(const int position, const int count)
{
  if (position < 0 || position + count > v_listSend.size())
    return;
  for (int row = position; row < position + count; row++)
  {
    // prendre la send et enlever le time
    OscSend *oscsend = getChild(row);
    int champ = oscsend->getChamp();
    m_timeWait -= oscsend->getTimewait();
    // Si c'est un fade on retranche aussi le time
    if (champ == P_FADE || champ == P_XFADE || champ == R_P_FADE || champ == R_P_XFADE) m_timeWait -= oscsend->getTime();
    delete v_listSend.takeAt(position);
  }
}

int OscSend::getSendId() const
{
  if (m_parentSend) return m_parentSend->v_listSend.indexOf(const_cast<OscSend *>(this));
  return 0;
}

void OscSend::moveChildPrev(const int position)
{
  if (position < 1 || position >= getSendCount()) return;
  v_listSend.swapItemsAt(position -1, position);
}

