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

#ifndef MYMIDIIN_H
#define MYMIDIIN_H

#include <QObject>
#include <rtmidi/RtMidi.h>
#include <iostream>
#include <QString>

// define API for RtMidi
#define __LINUX_ALSA__

const std::string apcmini = "APC MINI:APC MINI MIDI 1 24:0";
const std::string apcmini2 = "APC MINI:APC MINI MIDI 1 16:0";
const std::string myPortName = "MMControl Input Port";
const int control = 176;
const int buttonPressed = 144;
const int buttonReleased = 128;
const int opacity = 5;

class MyMidiIn : public QObject, public RtMidiIn
{
  Q_OBJECT
public:
  MyMidiIn(RtMidi::Api api = LINUX_ALSA,
           const std::string &clientName = "OscControlMapmap Input Client",
           unsigned int queueSizeLimit = 100);

  // Fn static pour le callback. Elle est statique mais elle peut accéder
  // aux fonctions des objets. On lui enverrra this en arg userData.
  static void sendMidiToOsc (double deltatime,
                             std::vector<unsigned char> *unMessage,
                             void *userData);

signals:
  void sigMidiCtrlChanged(int unID, float uneOpacite);
  void sigMidiNoteChanged(int unBouton);

private slots:
  void midiControlChanged(int unID, float uneOpacite);
  void midiNoteChanged(int unBouton);
};

#endif // MYMIDIIN_H
