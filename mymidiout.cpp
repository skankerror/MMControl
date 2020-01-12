#include "mymidiout.h"

MyMidiOut::MyMidiOut(int id, Api api, const std::string &clientName):
  QObject(),
  RtMidiOut(api, clientName)
{
  int nPorts = RtMidiOut::getPortCount();

  std::cout << "Api # : " << RtMidiOut::getCurrentApi() << "\n";
  std::cout << "Nombre de ports : " << nPorts << std::endl;
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
        std::cout << "Succés sur le port #" << i << std::endl;
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
        std::cout << "Succés sur le port #" << i << std::endl;
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
  if (RtMidiOut::isPortOpen()) std::cout << "Midi out " << id << " opened\n";
  else std::cout << "Midi out " << id << " not opened\n";
}
