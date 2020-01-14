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

#include "mymidiin.h"

MyMidiIn::MyMidiIn(int id, Api api, const std::string &clientName,
                   unsigned int queueSizeLimit):
  QObject(),
  RtMidiIn(api, clientName, queueSizeLimit)
{

  int nPorts = RtMidiIn::getPortCount();

  qDebug() << "Api # : " << RtMidiIn::getCurrentApi();
  qDebug() << "Nombre de ports : " << nPorts;
  for (int i = 0; i<nPorts; i++)
  {
    std::cout << "Port #" << i << " : " << RtMidiIn::getPortName(i) << std::endl;
  }

  ignoreTypes(); // Pour ignorer sysex et cie...
  switch(id)
  {
  case 1:
    for (int i = 0; i<nPorts; i++)
    {
      if (RtMidiIn::getPortName(i) == APCMINI_1)
      {
        RtMidiIn::openPort(i, MYPORTNAME_IN_1);  // On ouvre le port de l'APCMini
        qDebug() << "Succés sur le port #" << i;
        break;
      }
      else
      {
        std::cout << " Pas le bon nom : le nom système : " << RtMidiIn::getPortName(i)
                  << "\nLe nom programme : " << APCMINI_1  << std::endl;
      }
    }
    break;
  case 2:
    for (int i = 0; i<nPorts; i++)
    {
      if (RtMidiIn::getPortName(i) == APCMINI_2)
      {
        RtMidiIn::openPort(i, MYPORTNAME_IN_2);  // On ouvre le port de l'APCMini2
        qDebug() << "Succés sur le port #" << i;
        break;
      }
      else
      {
        std::cout << " Pas le bon nom : le nom système : " << RtMidiIn::getPortName(i)
                  << "\nLe nom programme : " << APCMINI_2  << std::endl;
      }
    }
  default: break;
  }
  // Pour lire les entrées avec callback
  RtMidiIn::setCallback(&sendMidiToOsc, this);
  if (RtMidiIn::isPortOpen()) qDebug() << "Midi in " << id << " opened\n";
  else qDebug() << "Midi in " << id << " not opened";
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

  unsigned int nBytes = unMessage->size(); // Pour voir le delta
  for ( unsigned int i=0; i<nBytes; i++ )
    qDebug() << "Byte " << i << " = " << (int)unMessage->at(i) << ", ";
  if ( nBytes > 0 )
    qDebug() << "stamp = " << deltatime;

  if ((int)unMessage->at(0) == MIDI_CONTROL)
  {
    qDebug() << "#0 : controller : ";
    int m_ID = (int)unMessage->at(1) - 47; // -47 car les sliders apc mini commencent leur ID à 48
    qDebug() << "paintID : " << m_ID;
    int m_temp  = (int)unMessage->at(2);
    float m_varFloat = (float)m_temp;
    m_varFloat /=127;
    qDebug() << " Opacity % : " << m_varFloat*100 << '\n';

    // Maintenant on y accède pour lancer le signal à *parent
    unMidiIn->midiControlChanged(m_ID, m_varFloat);
  }
  else if ((int)unMessage->at(0) == MIDI_BUTTON_PRESSED)
  {
    qDebug() << "Button " << (int)unMessage->at(1) << " pressed \n";
    unMidiIn->midiNoteChanged((int)unMessage->at(1));
  }

}
