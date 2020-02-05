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

#include "mymidi.h"

MyMidiIn::MyMidiIn(QObject *parent, Api api, const std::string &clientName,
                   unsigned int queueSizeLimit):
  QObject(parent),
  RtMidiIn(api, clientName, queueSizeLimit)
{}

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
  Q_UNUSED(deltatime)
  // On caste le void* pour pouvoir le déréférencer.
  MyMidiIn *unMidiIn = static_cast<MyMidiIn*>(userData);

  if ((int)unMessage->at(0) == MIDI_CONTROL)
  {
//    qDebug() << "#0 : controller : ";
    int m_ID = (int)unMessage->at(1) - 47; // -47 car les sliders apc mini commencent leur ID à 48
//    qDebug() << "paintID : " << m_ID;
    int m_temp  = (int)unMessage->at(2);
    float m_varFloat = (float)m_temp;
    m_varFloat /=127;
//    qDebug() << " Opacity % : " << m_varFloat*100 << '\n';

    // Maintenant on y accède pour lancer le signal à *parent
    unMidiIn->midiControlChanged(m_ID, m_varFloat);
  }
  else if ((int)unMessage->at(0) == MIDI_BUTTON_PRESSED)
  {
//    qDebug() << "Button " << (int)unMessage->at(1) << " pressed \n";
//    qDebug() << unMessage->at(0) << " " << unMessage->at(1) << " " << unMessage->at(2);
    unMidiIn->midiNoteChanged((int)unMessage->at(1));
  }

}

void MyMidiIn::connectMidiIn(int portNumber, int ID)
{
  ignoreTypes();
  if (ID == 1) RtMidiIn::openPort(portNumber, MYPORTNAME_IN_1);
  else RtMidiIn::openPort(portNumber, MYPORTNAME_IN_2);
  if (RtMidiIn::isPortOpen())
  {
//    qDebug() << "Midi in " << ID << " opened on port #" << portNumber;
    RtMidiIn::setCallback(&sendMidiToOsc, this);
  }
  else qDebug() << "Midi in " << ID << " not opened";
}

void MyMidiIn::disconnectMidiIn()
{
  if (RtMidiIn::isPortOpen())
  {
    RtMidiIn::closePort();
//    qDebug() << "Port in closed";
  }
  else qDebug() << "Port in was not opened...";
}

//*************************************************************************

MyMidiOut::MyMidiOut(QObject *parent, Api api, const std::string &clientName):
  QObject(parent),
  RtMidiOut(api, clientName)
{}

MyMidiOut::~MyMidiOut()
{
  if (RtMidiOut::isPortOpen())
  {
    MyMidiOut::allBoutonVisibleOff();
    MyMidiOut::allBoutonSoloOff();
    MyMidiOut::sendBoutonOff(83);
    MyMidiOut::sendBoutonOff(84);
    MyMidiOut::sendBoutonOff(86);
  }
}

void MyMidiOut::connectMidiOut(int portNumber, int ID)
{
  if (ID == 1) RtMidiOut::openPort(portNumber, MYPORTNAME_OUT_1);
  else RtMidiOut::openPort(portNumber, MYPORTNAME_OUT_2);
  if (RtMidiOut::isPortOpen()) /*qDebug() << "Midi Out " << ID << "opened on port #" << portNumber*/;
  else qDebug() << "Midi Out " << ID << " not opened";
}

void MyMidiOut::disconnectMidiOut()
{
  if (RtMidiOut::isPortOpen())
  {
    RtMidiOut::closePort();
//    qDebug() << "Port out closed";
  }
  else qDebug() << "Port out was not opened...";
}

void MyMidiOut::allBoutonVisibleOff()
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message; // on crée notre message et on l'initialise pour le 1er bouton
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(0);
  message.push_back(LIGHT_OFF);
  RtMidiOut::sendMessage(&message);
  for (int i = 1; i < 8; i++)
  {
    message[1] = i;
    RtMidiOut::sendMessage(&message);
  }
  message[1] = 89;
  RtMidiOut::sendMessage(&message);
}

void MyMidiOut::allBoutonVisibleOn()
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message; // on crée notre message et on l'initialise pour le 1er bouton
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(0);
  message.push_back(LIGHT_ON);
  RtMidiOut::sendMessage(&message);
  for (int i = 1; i < 8; i++)
  {
    message[1] = i;
    RtMidiOut::sendMessage(&message);
  }
  message[1] = 89;
  RtMidiOut::sendMessage(&message);
}

void MyMidiOut::allBoutonSoloOff()
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message; // on crée notre message
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(0);
  message.push_back(LIGHT_OFF);
  for (int i = 16; i < 24; i++)
  {
    message[1] = i;
    RtMidiOut::sendMessage(&message);
  }
  message[1] = 87;
  RtMidiOut::sendMessage(&message);
}

void MyMidiOut::allBoutonSoloOn()
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message; // on crée notre message
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(0);
  message.push_back(LIGHT_ON);
  for (int i = 16; i < 24; i++)
  {
    message[1] = i;
    RtMidiOut::sendMessage(&message);
  }
  message[1] = 87;
  RtMidiOut::sendMessage(&message);
}

void MyMidiOut::sendBoutonOn(int id)
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message;
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(id);
  message.push_back(LIGHT_ON);
  RtMidiOut::sendMessage(&message);
}

void MyMidiOut::sendBoutonOff(int id)
{
  if (!RtMidiOut::isPortOpen()) return;
  std::vector<unsigned char> message;
  message.push_back(MIDI_BUTTON_PRESSED);
  message.push_back(id);
  message.push_back(LIGHT_OFF);
  RtMidiOut::sendMessage(&message);
}

