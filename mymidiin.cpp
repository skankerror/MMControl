#include "mymidiin.h"

MyMidiIn::MyMidiIn(Api api, const std::string &clientName,
                   unsigned int queueSizeLimit) :
  QObject(),
  RtMidiIn(api, clientName, queueSizeLimit)
{

  int nPorts = RtMidiIn::getPortCount();

  std::cout << " Api # : " << RtMidiIn::getCurrentApi() << std::endl;
  std::cout << "Nombre de ports : " << nPorts << std::endl;
  for (int i = 0; i<nPorts; i++)
  {
    std::cout << "Port #" << i << " : " << RtMidiIn::getPortName(i) << std::endl;
  }

  ignoreTypes(); // Pour ignorer sysex et cie...

  for (int i = 0; i<nPorts; i++)
  {
    if (RtMidiIn::getPortName(i) == apcmini || RtMidiIn::getPortName(i) == apcmini2)
    {
      RtMidiIn::openPort(i, myPortName);  // On ouvre le port de l'APCMini
      std::cout << "Succés sur le port #" << i << std::endl;
      break;
    }
    else
    {
      std::cout << " Pas le bon nom : le nom système : " << RtMidiIn::getPortName(i)
                << "\nLe nom programme : " << apcmini << " ou " << apcmini2 << std::endl;
    }
  }

  // Pour lire les entrées avec callback
  RtMidiIn::setCallback(&sendMidiToOsc, this);
  std::cout << "J'écoute... ";

}
// Un slot qui appelle le signal connecté dans parent
void MyMidiIn::midiControlChanged(int unID, float uneOpacite)
{
  sigMidiCtrlChanged(unID, uneOpacite);
}

void MyMidiIn::midiNoteChanged(int unBouton)
{
  sigMidiNoteChanged(unBouton);
}

// La fonction appelée ds callback
void MyMidiIn::sendMidiToOsc(double deltatime,
                             std::vector<unsigned char> *unMessage,
                             void *userData) //on lui a passé this
{
  // On caste le void* pour pouvoir le déréférencer.
  MyMidiIn *unMidiIn = static_cast<MyMidiIn*>(userData);

  if ((int)unMessage->at(0) == control)
  {
    std::cout << "#0 : controller : ";
    int m_ID = (int)unMessage->at(1) - 47;
    std::cout << "paintID : " << m_ID;
    int m_temp  = (int)unMessage->at(2);
    float m_varFloat = (float)m_temp;
    m_varFloat /=127;
    std::cout << " Opacity % : " << m_varFloat*100 << '\n';

    // Maintenant on y accède pour lancer le signal à *parent
    unMidiIn->midiControlChanged(m_ID, m_varFloat);
  }
  else if ((int)unMessage->at(0) == buttonPressed)
  {
    std::cout << "Button " << (int)unMessage->at(1) << " pressed \n";
    unMidiIn->midiNoteChanged((int)unMessage->at(1));
  }

}
