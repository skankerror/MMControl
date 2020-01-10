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

// cstr 1: 0 NOOP, 1 PLAY, 2 PAUSE, 3 REWIND, 4 QUIT
OscSend::OscSend(champMM champ, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  if (m_champ > 4)
  {
    std::cout << "error osccend cstr 1 \n";
    return;
  }
}

// cstr 2: 5 P_NAME, 10 P_URI, 11 P_COLOR, 12 M_NAME, 22 R_P_OPACITY, 23 R_P_VOLUME,
// 24 R_P_RATE, 28 R_M_OPACITY, 32 R_M_DEPTH
OscSend::OscSend(champMM champ, int unInt, QString name, int time):
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  switch(m_champ)
  {
  case P_NAME: m_p_ID1 = unInt; m_p_name = name; break;
  case M_NAME: m_m_ID1 = unInt; m_m_name = name; break;
  case P_URI: m_p_ID1 = unInt; m_p_uri = name; break;
  case P_COLOR: m_p_ID1 = unInt; m_p_color = name; break;
  case R_P_OPACITY: m_p_name = name; m_p_opacity = unInt; break;
  case R_P_VOLUME: m_p_name = name; m_p_volume = unInt; break;
  case R_P_RATE: m_p_name = name; m_p_rate = unInt; break;
  case R_M_OPACITY: m_m_name = name; m_m_opacity = unInt; break;
  case R_M_DEPTH: m_m_name= name; m_m_depth = unInt; break;
  default: std::cout << "error oscsend cstr 2 \n"; return; break;
  }
}

// cstr 3: 6 P_REWIND
OscSend::OscSend(champMM champ,int p_ID1, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_p_ID1(p_ID1),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  if (m_champ != P_REWIND)
  {
    std::cout << "error oscsend cstr 3 \n";
    return;
  }
}

// cstr 4: 7 P_OPACITY, 8 P_VOLUME, 9 P_RATE, 13 M_OPACITY, 17 M_DEPTH, 18 P_XFADE
OscSend::OscSend(champMM champ, int ID1, int var,int time): 
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  switch(m_champ)
  {
  case P_OPACITY: m_p_ID1 = ID1; m_p_opacity = var; break;
  case P_VOLUME: m_p_ID1 = ID1; m_p_volume = var; ; break;
  case P_RATE: m_p_ID1 = ID1; m_p_rate = var; break;
  case M_OPACITY: m_m_ID1 = ID1; m_m_opacity = var; break;
  case M_DEPTH: m_m_ID1 = ID1; m_m_depth = var; break;
  case P_XFADE: m_p_ID1 = ID1; m_p_ID2 = var; break;
  default: std::cout << "error cstr 4 \n"; return; break;
  }
}

// cstr 5: 14 M_VISIBLE, 15 M_SOLO, 16 M_LOCK, 19 P_FADE
OscSend::OscSend(champMM champ, int ID1, bool isproperty, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  switch (m_champ)
  {
  case M_VISIBLE: m_m_ID1 = ID1; m_m_isvisible = isproperty; break;
  case M_SOLO: m_m_ID1 = ID1; m_m_issolo = isproperty; break;
  case M_LOCK: m_m_ID1 = ID1; m_m_islocked = isproperty; break;
  case P_FADE: m_p_ID1 = ID1; m_isfadein = isproperty; break;
  default:std::cout << "error cstr 5 \n"; return; break;
  }
}

// cstr 6 : 21 R_P_REWIND
OscSend::OscSend(champMM champ, QString name, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_p_name(name),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  if (m_champ != R_P_REWIND)
  {
    std::cout << "error cstr 6 \n";
    return;
  }
}

// cstr 7 : 20 R_P_NAME, 25 R_P_URI, 26 R_P_COLOR, 27 R_M_NAME, 34 R_P_XFADE
OscSend::OscSend(champMM champ, QString name1, QString name2, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  switch(m_champ)
  {
  case R_P_NAME: m_p_name = name1; m_p_name2 = name2; break;
  case R_P_URI: m_p_name = name1; m_p_uri = name2; break;
  case R_P_COLOR: m_p_name = name1; m_p_color = name2; break;
  case R_M_NAME: m_m_name = name1; ; break;
  case R_P_XFADE: m_p_name = name1; m_p_name2 = name2; break;
  default: std::cout << "error cstr 7 \n"; return; break;
  }
}

// CSTR 8 : 29 R_M_VISIBLE, 30 R_M_SOLO, 31 R_M_LOCK, 33 R_P_FADE
OscSend::OscSend(champMM champ, QString name, bool isproperty, int time):
  QObject(),
  UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
  m_champ(champ),
  m_time(time)/*,
  m_iswaiting(true)*/
{
  switch (m_champ)
  {
  case R_M_VISIBLE: m_m_name = name; m_m_isvisible = isproperty; break;
  case R_M_SOLO: m_m_name = name; m_m_issolo = isproperty; break;
  case R_M_LOCK: m_m_name = name; m_m_islocked = isproperty; break;
  case R_P_FADE: m_p_name = name; m_isfadein = isproperty; break;
  default: std::cout << "error cstr 8 \n"; return; break;
  }
}

void OscSend::ExecuteSend()
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);
  packet << osc::BeginBundleImmediate;
  switch (m_champ)
  {
  case NOOP: std::cout << "Noop... wait " << m_time << " s.\n"; /*usleep(1000000 * m_time);*/ break;
  case PLAY: packet << osc::BeginMessage("/mapmap/play") << osc::EndMessage;
    std::cout << "/mapmap/play\n"; break;
  case PAUSE: packet << osc::BeginMessage("/mapmap/pause") << osc::EndMessage;
    std::cout << "/mapmap/pause\n"; break;
  case REWIND: packet << osc::BeginMessage("/mapmap/rewind") << osc::EndMessage;
    std::cout << "/mapmap/rewind\n"; break;
  case QUIT: packet << osc::BeginMessage("/mapmap/quit") << osc::EndMessage;
    std::cout << "/mapmap/quit\n"; break;
  case P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_ID1 << m_p_name.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/name is " << m_p_ID1 << " " << m_p_name.toStdString().c_str() << std::endl; break;
  case P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_ID1 << osc::EndMessage;
    std::cout << "/mapmap/paint/rewind " << m_p_ID1 << " \n"; break;
  case P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_ID1 << ((float)m_p_opacity)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/opacity if " << m_p_ID1 << " " << ((float)m_p_opacity)/100 << std::endl; break;
  case P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_ID1 << ((float)m_p_volume)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/volume if " << m_p_ID1 << " " << ((float)m_p_volume)/100 << std::endl; break;
  case P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_ID1 << ((float)m_p_rate)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/rate if " << m_p_ID1 << " " << ((float)m_p_rate)/100 << std::endl; break;
  case P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_ID1 << m_p_uri.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/uri is " << m_p_ID1 << " " << m_p_uri.toStdString().c_str() << std::endl; break;
  case P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_ID1 << m_p_color.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/color is " << m_p_ID1 << m_p_color.toStdString().c_str() << std::endl; break;
  case M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_ID1 << m_m_name.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/mapping/name is " << m_m_ID1 << " " << m_m_name.toStdString().c_str() << std::endl; break;
  case M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_ID1 << ((float)m_m_opacity)/100 << osc::EndMessage;
    std::cout << "/mapmap/mapping/opacity if " << m_m_ID1 << " " << ((float)m_m_opacity)/100 << std::endl; break;
  case M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_ID1 << m_m_isvisible << osc::EndMessage;
    std::cout << "/mapmap/mapping/visible ii " << m_m_ID1 << m_m_isvisible << std::endl; break;
  case M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_ID1 << m_m_issolo << osc::EndMessage;
      std::cout << "/mapmap/mapping/solo ii " << m_m_ID1 << " " << m_m_issolo << std::endl; break;
  case M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_ID1 << m_m_islocked << osc::EndMessage;
      std::cout << "/mapmap/mapping/locked ii " << m_m_ID1 << " " << m_m_islocked << std::endl; break;
  case M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_ID1 << m_m_depth << osc::EndMessage;
    std::cout << "/mapmap/mapping/depth ii " << m_m_ID1 << " " << m_m_depth << std::endl; break;
  case P_XFADE: ExecuteXFade(m_p_ID1, m_p_ID2, m_time); break;
  case P_FADE: ExecuteFade(m_p_ID1, m_time, m_isfadein); break;
  case R_P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_name.toStdString().c_str() << m_p_name2.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/name ss " << m_p_name.toStdString().c_str() << " " << m_p_name2.toStdString().c_str() << std::endl; break;
  case R_P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_name.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/rewind s " << m_p_name.toStdString().c_str() << std::endl; break;
  case R_P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_name.toStdString().c_str() << ((float)m_p_opacity)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/opacity sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_opacity)/100 << std::endl; break;
  case R_P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_name.toStdString().c_str() << ((float)m_p_volume)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/volume sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_volume)/100 << std::endl; break;
  case R_P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_name.toStdString().c_str() << ((float)m_p_rate)/100 << osc::EndMessage;
    std::cout << "/mapmap/paint/rate sf " << m_p_name.toStdString().c_str() << " " << ((float)m_p_rate)/100 << std::endl; break;
  case R_P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_name.toStdString().c_str() << m_p_uri.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/uri ss " << m_p_name.toStdString().c_str() << " " << m_p_uri.toStdString().c_str() << std::endl; break;
  case R_P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_name.toStdString().c_str() << m_p_color.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/paint/color ss " << m_p_name.toStdString().c_str() << " " << m_p_color.toStdString().c_str() << std::endl; break;
  case R_M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_name.toStdString().c_str() << m_m_name2.toStdString().c_str() << osc::EndMessage;
    std::cout << "/mapmap/mapping/name ss " << m_m_name.toStdString().c_str() << " " << m_m_name2.toStdString().c_str() << std::endl; break;
  case R_M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_name.toStdString().c_str() << m_m_opacity << osc::EndMessage;
    std::cout << "/mapmap/mapping/opacity si " << m_m_name.toStdString().c_str() << " " << m_m_opacity << std::endl; break;
  case R_M_VISIBLE: packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_name.toStdString().c_str() << m_m_isvisible << osc::EndMessage;
    std::cout << "/mapmap/mapping/visible si " << m_m_name.toStdString().c_str() << m_m_isvisible << std::endl; break;
  case R_M_SOLO: packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_name.toStdString().c_str() << m_m_issolo << osc::EndMessage;
    std::cout << "/mapmap/mapping/solo si " << m_m_name.toStdString().c_str() << " " << m_m_issolo << std::endl; break;
  case R_M_LOCK: packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_name.toStdString().c_str() << m_m_islocked << osc::EndMessage;
    std::cout << "/mapmap/mapping/locked si " << m_m_name.toStdString().c_str() << " " << m_m_islocked << std::endl; break;
  case R_M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_name.toStdString().c_str() << m_m_depth << osc::EndMessage;
    std::cout << "/mapmap/mapping/depth si " << m_m_name.toStdString().c_str() << " " << m_m_depth << std::endl; break;
  case R_P_FADE: ExecutePFade(m_p_name, m_time, m_isfadein); break;
  case R_P_XFADE: ExecutePXFade(m_p_name, m_p_name2, m_time); break;
  default: packet << osc::BeginMessage("/error_default_champ") << osc::EndMessage;
    std::cout << "/sa/pa/normal error execute send\n"; break;
  }

  packet << osc::EndBundle;
  Send(packet.Data(), packet.Size());
}
void OscSend::ExecuteXFade(int ID1, int ID2, int time)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);

  for (float i = 0; i<=1; i += 0.01)
  {
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

    usleep(10000 * time);
  }
}
void OscSend::ExecuteFade(int ID1, int time, bool isfadein)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);

  for (float i = 0; i<=1; i += 0.01)
  {

    packet << osc::BeginBundleImmediate
           << osc::BeginMessage("/mapmap/paint/opacity") << ID1;
    if (isfadein)
      packet << i;
    else
      packet << 1 - i;
    packet << osc::EndMessage << osc::EndBundle;

    usleep(10000 * time);
    Send(packet.Data(), packet.Size());
    std::cout << "bluk\n";
    packet.Clear();
  }
}

void OscSend::ExecutePXFade(QString p_name, QString p_name2, int time)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);

  for (float i = 0; i<=1; i += 0.01)
  {
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

    usleep(10000 * time);
  }
}
void OscSend::ExecutePFade(QString p_name, int time, bool isfadein)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream packet(buffer, OUTPUT_BUFFER_SIZE);

  for (float i = 0; i<=1; i += 0.01)
  {

    packet << osc::BeginBundleImmediate
           << osc::BeginMessage("/mapmap/paint/opacity") << p_name.toStdString().c_str();
    if (isfadein)
      packet << i;
    else
      packet << 1 - i;
    packet << osc::EndMessage << osc::EndBundle;

    usleep(10000 * time);
    Send(packet.Data(), packet.Size());
    std::cout << "bluk\n";
    packet.Clear();
  }
}
