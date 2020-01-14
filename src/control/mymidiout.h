#ifndef MYMIDIOUT_H
#define MYMIDIOUT_H

#include <QObject>
#include <rtmidi/RtMidi.h>
#include <iostream>
#include <QString>
#include <QDebug>
#include "MMC.h"

class MyMidiOut : public QObject, public RtMidiOut
{
  Q_OBJECT
public:
  MyMidiOut(int id = 1,
            RtMidi::Api api = LINUX_ALSA,
            const std::string &clientName = "MMControl Output Client");
};

#endif // MYMIDIOUT_H
