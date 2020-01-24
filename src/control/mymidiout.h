#ifndef MYMIDIOUT_H
#define MYMIDIOUT_H

#include <QObject>
#include <rtmidi/RtMidi.h>
#include <QString>
#include <QDebug>
#include "MMC.h"

class MyMidiOut : public QObject, public RtMidiOut
{
  Q_OBJECT
public:
  MyMidiOut(int id = 1, QObject *parent = nullptr,
            RtMidi::Api api = LINUX_ALSA,
            const std::string &clientName = "MMControl Output Client");
};

#endif // MYMIDIOUT_H
