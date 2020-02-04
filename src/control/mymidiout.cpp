#include "mymidiout.h"

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
