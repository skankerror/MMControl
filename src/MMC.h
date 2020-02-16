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

#include <QBrush>

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
  PLAY, PAUSE, REWIND, QUIT, P_NAME, P_REWIND, P_OPACITY, P_VOLUME,
  P_RATE, P_URI, P_COLOR, M_NAME, M_OPACITY, M_VISIBLE, M_SOLO, M_LOCK,
  M_DEPTH, P_XFADE, P_FADE, R_P_NAME, R_P_REWIND, R_P_OPACITY, R_P_VOLUME,
  R_P_RATE, R_P_URI, R_P_COLOR, R_M_NAME, R_M_OPACITY, R_M_VISIBLE, R_M_SOLO,
  R_M_LOCK, R_M_DEPTH, R_P_FADE, R_P_XFADE, CUE, Count_champMM = CUE + 1
};

// OscCueList
enum columns
{
  Champ, P_name, P_name2, Uri, Color, P_Id, P_Id2, Rate, P_opac, Vol,
  M_name, M_name2, M_Id, M_opac, Visible, Solo, Lock, Depth,
  Fade_In, Time, Wait, Note, Count = Note + 1
};
#define SALMONCOLOR "#725651"
#define YELLOWCOLOR "#818658"
#define YELLOWCOLOR2 "#7D8256"
#define GREENCOLOR "#2F7539"
#define ORANGECOLOR /*"#BA6D2B"*/ "#944C0F"
#define BLUECOLOR "#3C559A"
#define REDCOLOR "#730A0C"

// MyMidiIn
#define __LINUX_ALSA // define API for RtMidi needed by MyMidiIn class
#define APCMINI_1 "APC MINI:APC MINI MIDI 1 24:0"
#define APCMINI_2 "APC MINI:APC MINI MIDI 1 28:0"
#define MYPORTNAME_IN_1 "MMControl Input Port 1"
#define MYPORTNAME_IN_2 "MMControl Input Port 2"
#define MYPORTNAME_OUT_1 "MMControl Output Port 1"
#define MYPORTNAME_OUT_2 "MMControl Output Port 2"
#define MIDI_CONTROL 176
#define MIDI_BUTTON_PRESSED 144
#define LIGHT_ON 01
#define LIGHT_OFF 00
#define QUEUE_SIZE_LIMIT 100

#endif // MMC_H
