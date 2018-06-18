#ifndef OSCSEND_H
#define OSCSEND_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QColor>
//#include <QStandardItem>
#include <iostream>
#include <unistd.h>
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"
#include "oscpack/ip/NetworkingUtils.h"
#include "oscpack/ip/IpEndpointName.h"

#define ADDRESS "127.0.0.1" // IP cible
#define PORT 12345 // Port cible

#define OUTPUT_BUFFER_SIZE 512

enum champMM
{
    NOOP = 0,
    PLAY = 1,
    PAUSE = 2,
    REWIND = 3,
    QUIT = 4,
    P_NAME = 5,
    P_REWIND = 6,
    P_OPACITY = 7,
    P_VOLUME = 8,
    P_RATE = 9,
    P_URI = 10,
    P_COLOR = 11,
    M_NAME = 12,
    M_OPACITY = 13,
    M_VISIBLE = 14,
    M_SOLO = 15,
    M_LOCK = 16,
    M_DEPTH = 17,
    P_XFADE = 18,
    P_FADE = 19
};

class OscSend : public QObject,
        public UdpTransmitSocket
        //public QStandardItem
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

    void ExecuteSend();
    void ExecuteXFade(int ID1, int ID2, int time);
    void ExecuteFade(int ID1, int time, bool isfadein);

// private:
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
};

#endif // OSCSEND_H
