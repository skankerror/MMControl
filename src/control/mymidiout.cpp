#include "mymidiout.h"

MyMidiOut::MyMidiOut(int id, Api api, const std::string &clientName):
  QObject(),
  RtMidiOut(api, clientName)
{
  int nPorts = RtMidiOut::getPortCount();

  qDebug() << "Api # : " << RtMidiOut::getCurrentApi();
  qDebug() << "Nombre de ports : " << nPorts;
  for (int i = 0; i<nPorts; i++)
  {
    std::cout << "Port #" << i << " : " << RtMidiOut::getPortName(i) << std::endl;
  }
  switch(id)
  {
  case 1:
    for (int i = 0; i<nPorts; i++)
    {
      if (RtMidiOut::getPortName(i) == APCMINI_1)
      {
        RtMidiOut::openPort(i, MYPORTNAME_OUT_1);  // On ouvre le port de l'APCMini
        qDebug() << "Succés sur le port #" << i;
        break;
      }
      else
      {
        std::cout << " Pas le bon nom : le nom système : " << RtMidiOut::getPortName(i)
                  << "\nLe nom programme : " << APCMINI_1  << std::endl;
      }
    }
    break;
  case 2:
    for (int i = 0; i<nPorts; i++)
    {
      if (RtMidiOut::getPortName(i) == APCMINI_2)
      {
        RtMidiOut::openPort(i, MYPORTNAME_OUT_2);  // On ouvre le port de l'APCMini2
        qDebug() << "Succés sur le port #" << i;
        break;
      }
      else
      {
        std::cout << " Pas le bon nom : le nom système : " << RtMidiOut::getPortName(i)
                  << "\nLe nom programme : " << APCMINI_2  << std::endl;
      }
    }
  default: break;
  }
  if (RtMidiOut::isPortOpen()) qDebug() << "Midi out " << id << " opened";
  else qDebug() << "Midi out " << id << " not opened";
}
