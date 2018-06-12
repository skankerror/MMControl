#include "oscsend.h"

OscSend::OscSend(champMM champ, int time): // 0, 1, 2, 3, 4
    QObject(),
    UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
    QStandardItem(),
    m_champ(champ),
    m_time(time)
{
    if (m_champ > 4)
    {
        std::cout << "Error champMM > 4 \n";
        return;
    }
    else
    {
        if (m_champ == NOOP)
        {
            std::cout << "OscSend created noop...\n";
        }
    }
}
OscSend::OscSend(champMM champ, int ID1,
                 QString name, int time): // 5, 12
    QObject(),
    UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
    QStandardItem(),
    m_champ(champ),
    m_time(time)
{
    if (m_champ != P_NAME && m_champ != M_NAME && m_champ != P_URI && m_champ != P_COLOR)
    {
        std::cout << "champMM ne correspond pas à un NAME, URI !\n";
        return;
    }
    if (m_champ == P_NAME)
    {
        m_p_ID1 = ID1;
        m_p_name = name;
    }
    if (m_champ == M_NAME)
    {
        m_m_ID1 = ID1;
        m_m_name = name;
    }
    if (m_champ == P_URI)
    {
        m_p_ID1 = ID1;
        m_p_uri = name;
    }
    if (m_champ == P_COLOR)
    {
        m_p_ID1 = ID1;
        m_p_color = name;
    }
}
OscSend::OscSend(champMM champ,int p_ID1, int time): // 6
    QObject(),
    UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
    QStandardItem(),
    m_champ(champ),
    m_p_ID1(p_ID1),
    m_time(time)
{
    if (m_champ != P_REWIND)
    {
        std::cout << "Error, rewind expected !\n";
        return;
    }
}
OscSend::OscSend(champMM champ, int ID1, int var,
        int time): // 7, 8, 9, 13, 17, 18
    QObject(),
    UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
    QStandardItem(),
    m_champ(champ),
    m_time(time)
{
    switch(m_champ)
    {
    case P_OPACITY: m_p_ID1 = ID1; m_p_opacity = var; break;
    case P_VOLUME: m_p_ID1 = ID1; m_p_volume = var; break;
    case P_RATE: m_p_ID1 = ID1; m_p_rate = var; break;
    case M_OPACITY: m_m_ID1 = ID1; m_m_opacity = var; break;
    case M_DEPTH: m_m_ID1 = ID1; m_m_depth = var; break;
    case P_XFADE: m_p_ID1 = ID1; m_p_ID2 = var; break;
    default: std::cout << "Error champ don't match !\n"; break;
    }
}
OscSend::OscSend(champMM champ, int ID1, bool isproperty,
        int time): // 14, 15, 16, 19
    QObject(),
    UdpTransmitSocket(IpEndpointName(ADDRESS, PORT)),
    QStandardItem(),
    m_champ(champ),
    m_time(time)
{
    switch (m_champ)
    {
    case M_VISIBLE: m_m_ID1 = ID1; m_m_isvisible = isproperty; break;
    case M_SOLO: m_m_ID1 = ID1; m_m_issolo = isproperty; break;
    case M_LOCK: m_m_ID1 = ID1; m_m_islocked = isproperty; break;
    case P_FADE: m_p_ID1 = ID1; m_isfadein = isproperty; break;
    default:std::cout << "Error, champ not expected !\n"; break;
    }
}

void OscSend::ExecuteSend()
{
    char buffer[512];
    osc::OutboundPacketStream packet(buffer, 512);
    packet << osc::BeginBundleImmediate;
    switch (m_champ) //
    {
    case NOOP: std::cout << "Noop...\n"; break;
    case PLAY: packet << osc::BeginMessage("/mapmap/play") << osc::EndMessage;
        std::cout << "/mapmap/play\n"; break;
    case PAUSE: packet << osc::BeginMessage("/mapmap/pause") << osc::EndMessage;
        std::cout << "/mapmap/pause\n"; break;
    case REWIND: packet << osc::BeginMessage("/mapmap/rewind") << osc::EndMessage;
        std::cout << "/mapmap/rewind\n"; break;
    case QUIT: packet << osc::BeginMessage("/mapmap/quit") << osc::EndMessage;
        std::cout << "/mapmap/quit\n"; break;
    case P_NAME: packet << osc::BeginMessage("/mapmap/paint/name") << m_p_ID1
                        << m_p_name.toStdString().c_str() << osc::EndMessage;
        std::cout << "/mapmap/paint/name is " << m_p_ID1 << " "
                  << m_p_name.toStdString().c_str() << std::endl; break;
    case P_REWIND: packet << osc::BeginMessage("/mapmap/paint/rewind") << m_p_ID1
                          << osc::EndMessage;
        std::cout << "/mapmap/paint/rewind " << m_p_ID1 << " \n"; break;
    case P_OPACITY: packet << osc::BeginMessage("/mapmap/paint/opacity") << m_p_ID1
               << ((float)m_p_opacity)/100 << osc::EndMessage;
        std::cout << "/mapmap/paint/opacity if " << m_p_ID1 << " "
                  << ((float)m_p_opacity)/100 << std::endl; break;
    case P_VOLUME: packet << osc::BeginMessage("/mapmap/paint/volume") << m_p_ID1
               << ((float)m_p_volume)/100 << osc::EndMessage;
        std::cout << "/mapmap/paint/volume if " << m_p_ID1 << " "
                  << ((float)m_p_volume)/100 << std::endl; break;
    case P_RATE: packet << osc::BeginMessage("/mapmap/paint/rate") << m_p_ID1
               << ((float)m_p_rate)/100 << osc::EndMessage;
        std::cout << "/mapmap/paint/rate if " << m_p_ID1 << " "
                  << ((float)m_p_rate)/100 << std::endl; break;
    case P_URI: packet << osc::BeginMessage("/mapmap/paint/uri") << m_p_ID1
                       << m_p_uri.toStdString().c_str() << osc::EndMessage;
        std::cout << "/mapmap/paint/uri is " << m_p_ID1 << " "
                  << m_p_uri.toStdString().c_str() << std::endl; break;
    case P_COLOR: packet << osc::BeginMessage("/mapmap/paint/color") << m_p_ID1
                         << m_p_color.toStdString().c_str() << osc::EndMessage;
        std::cout << "/mapmap/paint/color is " << m_p_ID1
                  << m_p_color.toStdString().c_str() << std::endl; break;
    case M_NAME: packet << osc::BeginMessage("/mapmap/mapping/name") << m_m_ID1
                        << m_m_name.toStdString().c_str() << osc::EndMessage;
        std::cout << "/mapmap/mapping/name is " << m_m_ID1 << " "
                  << m_m_name.toStdString().c_str() << std::endl; break;
    case M_OPACITY: packet << osc::BeginMessage("/mapmap/mapping/opacity") << m_m_ID1
                           << ((float)m_m_opacity)/100 << osc::EndMessage;
        std::cout << "/mapmap/mapping/opacity if " << m_m_ID1 << " "
                  << ((float)m_m_opacity)/100 << std::endl; break;
    case M_VISIBLE: if (m_m_isvisible)
        {
            packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_ID1
                           << 1 << osc::EndMessage;
            std::cout << "/mapmap/mapping/visible ii " << m_m_ID1 << " 1\n" ;break;
        }
        else
        {
            packet << osc::BeginMessage("/mapmap/mapping/visible") << m_m_ID1
                           << 0 << osc::EndMessage;
            std::cout << "/mapmap/mapping/visible ii " << m_m_ID1 << " 0\n" ;break;
        }
    case M_SOLO: if (m_m_issolo)
        {
            packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_ID1
                           << 1 << osc::EndMessage;
            std::cout << "/mapmap/mapping/solo ii " << m_m_ID1 << " 1\n" ;break;
        }
        else
        {
            packet << osc::BeginMessage("/mapmap/mapping/solo") << m_m_ID1
                           << 0 << osc::EndMessage;
            std::cout << "/mapmap/mapping/solo ii " << m_m_ID1 << " 0\n" ;break;
        }
    case M_LOCK: if (m_m_islocked)
        {
            packet << osc::BeginMessage("/mapmap/mapping/locked") << m_m_ID1
                           << 1 << osc::EndMessage;
            std::cout << "/mapmap/mapping/locked ii " << m_m_ID1 << " 1\n" ;break;
        }
        else
        {
            packet << osc::BeginMessage("/mapmap/mapping/lock") << m_m_ID1
                           << 0 << osc::EndMessage;
            std::cout << "/mapmap/mapping/lock ii " << m_m_ID1 << " 0\n" ;break;
        }
    case M_DEPTH: packet << osc::BeginMessage("/mapmap/mapping/depth") << m_m_ID1
                         << m_m_depth << osc::EndMessage;
        std::cout << "/mapmap/mapping/depth ii " << m_m_ID1 << " " << m_m_depth
                  << std::endl; break;
    case P_XFADE: ExecuteXFade(m_p_ID1, m_p_ID2, m_time); break;
    case P_FADE: ExecuteFade(m_p_ID1, m_time, m_isfadein); break;
    default: packet << osc::BeginMessage("/error_default_champ") << osc::EndMessage;
        std::cout << "/sa/pa/normal !! default champ !!\n"; break;
    }

    packet << osc::EndBundle;
    Send(packet.Data(), packet.Size());
}
void OscSend::ExecuteXFade(int ID1, int ID2, int time)
{
    char buffer[512];
    osc::OutboundPacketStream packet(buffer, 512);

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
    char buffer[512];
    osc::OutboundPacketStream packet(buffer, 512);

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

