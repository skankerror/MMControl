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
  MyMidiOut(QObject *parent = nullptr,
            RtMidi::Api api = LINUX_ALSA,
            const std::string &clientName = "MMControl Output Client");
  ~MyMidiOut();

public slots:
  void connectMidiOut(int portNumber, int ID);
  void disconnectMidiOut();
  void allBoutonVisibleOff();
  void allBoutonVisibleOn();
  void allBoutonSoloOff();
  void allBoutonSoloOn();
  void sendBoutonOn(int id);
  void sendBoutonOff(int id);

};

#endif // MYMIDIOUT_H
