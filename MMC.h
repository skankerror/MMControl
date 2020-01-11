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

#ifndef MMC_H
#define MMC_H

// MainWindow
#define WINDOW_TITLE "Mapmap Controller"
#define X_WINDOW_OFFSET 200
#define Y_WINDOW_OFFSET 200
#define WINDOW_WIDTH 1424
#define WINDOW_HEIGHT 768

// OscSend
#define ADDRESS "127.0.0.1" // IP cible
#define PORT 12345 // Port cible
#define OUTPUT_BUFFER_SIZE 512
enum champMM
{
  NOOP = 0,
  PLAY = 1,
  PAUSE = 2,
  REWIND = 3,
  QUIT = 4,
  P_NAME = 5,
  P_REWIND = 6,
  P_OPACITY = 7,
  P_VOLUME = 8,
  P_RATE = 9,
  P_URI = 10,
  P_COLOR = 11,
  M_NAME = 12,
  M_OPACITY = 13,
  M_VISIBLE = 14,
  M_SOLO = 15,
  M_LOCK = 16,
  M_DEPTH = 17,
  P_XFADE = 18,
  P_FADE = 19,
  R_P_NAME = 20,
  R_P_REWIND = 21,
  R_P_OPACITY = 22,
  R_P_VOLUME = 23,
  R_P_RATE = 24,
  R_P_URI = 25,
  R_P_COLOR = 26,
  R_M_NAME = 27,
  R_M_OPACITY = 28,
  R_M_VISIBLE = 29,
  R_M_SOLO = 30,
  R_M_LOCK = 31,
  R_M_DEPTH = 32,
  R_P_FADE = 33,
  R_P_XFADE = 34
};

// MyMidiIn
#define __LINUX_ALSA // define API for RtMidi needed by MyMidiIn class
#define APCMINI_1 "APC MINI:APC MINI MIDI 1 24:0"
#define APCMINI_2 "APC MINI:APC MINI MIDI 1 28:0"
#define MYPORTNAME_1 "MMControl Input Port 1"
#define MYPORTNAME_2 "MMControl Input Port 2"
#define MIDI_CONTROL 176
#define MIDI_BUTTON_PRESSED 144
#define QUEUE_SIZE_LIMIT 100

#endif // MMC_H
