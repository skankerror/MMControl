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

#ifndef TABMIDI_H
#define TABMIDI_H

#include <QtWidgets>
#include "mymidiin.h"
#include "mymidiout.h"
#include "oscsend.h"

class TabMidi : public QWidget
{
  Q_OBJECT
public:
  explicit TabMidi(MyMidiIn *midiIn1,
                   MyMidiIn *midiIn2,
                   MyMidiOut *midiOut1,
                   MyMidiOut *midiOut2,
                   QWidget *parent = nullptr);

signals:

public slots:
  // APCMINI 1
  void receiveMidiCtrl(int unID, float uneOpacite);

  void sendOscS1(int uneOpacite); void sendOscS2(int uneOpacite); void sendOscS3(int uneOpacite); void sendOscS4(int uneOpacite); void sendOscS5(int uneOpacite);
  void sendOscS6(int uneOpacite); void sendOscS7(int uneOpacite); void sendOscS8(int uneOpacite); void sendOscS9(int uneOpacite);

  void receiveMidiNote(int unBouton);

  void sendOscAPCB64(); void sendOscAPCB65(); void sendOscAPCB66(); void sendOscAPCB67();
  void sendOscAPCB68(); void sendOscAPCB69(); void sendOscAPCB70(); void sendOscAPCB71(); void sendOscAPCB98();

  void sendOscAPCB0(); void sendOscAPCB1(); void sendOscAPCB2(); void sendOscAPCB3(); void sendOscAPCB4();
  void sendOscAPCB5(); void sendOscAPCB6(); void sendOscAPCB7(); void sendOscAPCB89();

  void sendOscAPCB8(); void sendOscAPCB9(); void sendOscAPCB10(); void sendOscAPCB11();
  void sendOscAPCB12(); void sendOscAPCB13(); void sendOscAPCB14(); void sendOscAPCB15(); void sendOscAPCB88();

  void sendOscAPCB16(); void sendOscAPCB17(); void sendOscAPCB18(); void sendOscAPCB19();
  void sendOscAPCB20(); void sendOscAPCB21(); void sendOscAPCB22(); void sendOscAPCB23(); void sendOscAPCB87();

  void sendOscAPCB24(); void sendOscAPCB25(); void sendOscAPCB26(); void sendOscAPCB27();
  void sendOscAPCB28(); void sendOscAPCB29(); void sendOscAPCB30(); void sendOscAPCB31(); void sendOscAPCB86();

  void sendOscAPCB32(); void sendOscAPCB33(); void sendOscAPCB34(); void sendOscAPCB35();
  void sendOscAPCB36(); void sendOscAPCB37(); void sendOscAPCB38(); void sendOscAPCB39(); void sendOscAPCB85();

  void sendOscAPCB40(); void sendOscAPCB41(); void sendOscAPCB42(); void sendOscAPCB43();
  void sendOscAPCB44(); void sendOscAPCB45(); void sendOscAPCB46(); void sendOscAPCB47(); void sendOscAPCB84();

  void sendOscAPCB48(); void sendOscAPCB49(); void sendOscAPCB50(); void sendOscAPCB51();
  void sendOscAPCB52(); void sendOscAPCB53(); void sendOscAPCB54(); void sendOscAPCB55(); void sendOscAPCB83();

  void sendOscAPCB56(); void sendOscAPCB57(); void sendOscAPCB58(); void sendOscAPCB59();
  void sendOscAPCB60(); void sendOscAPCB61(); void sendOscAPCB62(); void sendOscAPCB63(); void sendOscAPCB82();

  // APCMINI 2
  void receiveMidiCtrl2(int unID, float uneOpacite);

  void sendOscS10(int uneOpacite); void sendOscS11(int uneOpacite); void sendOscS12(int uneOpacite); void sendOscS13(int uneOpacite); void sendOscS14(int uneOpacite);
  void sendOscS15(int uneOpacite); void sendOscS16(int uneOpacite); void sendOscS17(int uneOpacite); void sendOscS18(int uneOpacite);

  void receiveMidiNote2(int unBouton);

  void sendOscAPCB64_2(); void sendOscAPCB65_2(); void sendOscAPCB66_2(); void sendOscAPCB67_2();
  void sendOscAPCB68_2(); void sendOscAPCB69_2(); void sendOscAPCB70_2(); void sendOscAPCB71_2(); void sendOscAPCB98_2();

  void sendOscAPCB0_2(); void sendOscAPCB1_2(); void sendOscAPCB2_2(); void sendOscAPCB3_2(); void sendOscAPCB4_2();
  void sendOscAPCB5_2(); void sendOscAPCB6_2(); void sendOscAPCB7_2(); void sendOscAPCB89_2();

  void sendOscAPCB8_2(); void sendOscAPCB9_2(); void sendOscAPCB10_2(); void sendOscAPCB11_2();
  void sendOscAPCB12_2(); void sendOscAPCB13_2(); void sendOscAPCB14_2(); void sendOscAPCB15_2(); void sendOscAPCB88_2();

  void sendOscAPCB16_2(); void sendOscAPCB17_2(); void sendOscAPCB18_2(); void sendOscAPCB19_2();
  void sendOscAPCB20_2(); void sendOscAPCB21_2(); void sendOscAPCB22_2(); void sendOscAPCB23_2(); void sendOscAPCB87_2();

  void sendOscAPCB24_2(); void sendOscAPCB25_2(); void sendOscAPCB26_2(); void sendOscAPCB27_2();
  void sendOscAPCB28_2(); void sendOscAPCB29_2(); void sendOscAPCB30_2(); void sendOscAPCB31_2(); void sendOscAPCB86_2();

  void sendOscAPCB32_2(); void sendOscAPCB33_2(); void sendOscAPCB34_2(); void sendOscAPCB35_2();
  void sendOscAPCB36_2(); void sendOscAPCB37_2(); void sendOscAPCB38_2(); void sendOscAPCB39_2(); void sendOscAPCB85_2();

  void sendOscAPCB40_2(); void sendOscAPCB41_2(); void sendOscAPCB42_2(); void sendOscAPCB43_2();
  void sendOscAPCB44_2(); void sendOscAPCB45_2(); void sendOscAPCB46_2(); void sendOscAPCB47_2(); void sendOscAPCB84_2();

  void sendOscAPCB48_2(); void sendOscAPCB49_2(); void sendOscAPCB50_2(); void sendOscAPCB51_2();
  void sendOscAPCB52_2(); void sendOscAPCB53_2(); void sendOscAPCB54_2(); void sendOscAPCB55_2(); void sendOscAPCB83_2();

  void sendOscAPCB56_2(); void sendOscAPCB57_2(); void sendOscAPCB58_2(); void sendOscAPCB59_2();
  void sendOscAPCB60_2(); void sendOscAPCB61_2(); void sendOscAPCB62_2(); void sendOscAPCB63_2(); void sendOscAPCB82_2();

  // slots connexions midi
  void getPortNames();void slotConnectMidi1(); void slotConnectMidi2();
  void slotDisconnectMidi1(); void slotDisconnectMidi2();

private:
  OscSend *oscSendS; // Pour les sliders
  OscSend *oscSendB; // Pour les Boutons
  MyMidiIn *m_midiIn1;
  MyMidiIn *m_midiIn2;
  MyMidiOut *m_midiOut1;
  MyMidiOut *m_midiOut2;

  QGridLayout *layoutTotal;

  // Sliders et spinboxs, 3 dernières lignes // changer spinboxes 18 en label
  QSlider *S1; QSlider *S2; QSlider *S3; QSlider *S4; QSlider *S5; QSlider *S6; QSlider *S7; QSlider *S8; QSlider *S9; //apc 1
  QSpinBox *pID1; QSpinBox *pID2; QSpinBox *pID3; QSpinBox *pID4; QSpinBox *pID5; QSpinBox *pID6; QSpinBox *pID7; QSpinBox *pID8; QSpinBox *pID9; //apc1
  QSpinBox *mID1; QSpinBox *mID2; QSpinBox *mID3; QSpinBox *mID4; QSpinBox *mID5; QSpinBox *mID6; QSpinBox *mID7; QSpinBox *mID8; QSpinBox *mID9;
  QSlider *S10; QSlider *S11; QSlider *S12; QSlider *S13; QSlider *S14; QSlider *S15; QSlider *S16; QSlider *S17; QSlider *S18; //apc2
  QSpinBox *pID10; QSpinBox *pID11; QSpinBox *pID12; QSpinBox *pID13; QSpinBox *pID14; QSpinBox *pID15; QSpinBox *pID16; QSpinBox *pID17; /*QSpinBox *pID18;*/ //apc2
  QSpinBox *mID10; QSpinBox *mID11; QSpinBox *mID12; QSpinBox *mID13; QSpinBox *mID14; QSpinBox *mID15; QSpinBox *mID16; QSpinBox *mID17; /*QSpinBox *mID18;*/
  QLabel *labelMaster;

  // Labels 1ère colonne
  QLabel *labelb9; QLabel *labelb8; QLabel *labelb7; QLabel *labelb6; QLabel *labelb5; QLabel *labelb4; QLabel *labelb3; QLabel *labelb2; QLabel *labelb1;
  QLabel *labelS; QLabel *labelPid; QLabel *labelMid;

  // Boutons apc1
  QPushButton *B64; QPushButton *B0; QPushButton *B8; QPushButton *B16; QPushButton *B24; QPushButton *B32; QPushButton *B40; QPushButton *B48; QPushButton *B56;
  QPushButton *B65; QPushButton *B1; QPushButton *B9; QPushButton *B17; QPushButton *B25; QPushButton *B33; QPushButton *B41; QPushButton *B49; QPushButton *B57;
  QPushButton *B66; QPushButton *B2; QPushButton *B10; QPushButton *B18; QPushButton *B26; QPushButton *B34; QPushButton *B42; QPushButton *B50; QPushButton *B58;
  QPushButton *B67; QPushButton *B3; QPushButton *B11; QPushButton *B19; QPushButton *B27; QPushButton *B35; QPushButton *B43; QPushButton *B51; QPushButton *B59;
  QPushButton *B68; QPushButton *B4; QPushButton *B12; QPushButton *B20; QPushButton *B28; QPushButton *B36; QPushButton *B44; QPushButton *B52; QPushButton *B60;
  QPushButton *B69; QPushButton *B5; QPushButton *B13; QPushButton *B21; QPushButton *B29; QPushButton *B37; QPushButton *B45; QPushButton *B53; QPushButton *B61;
  QPushButton *B70; QPushButton *B6; QPushButton *B14; QPushButton *B22; QPushButton *B30; QPushButton *B38; QPushButton *B46; QPushButton *B54; QPushButton *B62;
  QPushButton *B71; QPushButton *B7; QPushButton *B15; QPushButton *B23; QPushButton *B31; QPushButton *B39; QPushButton *B47; QPushButton *B55; QPushButton *B63;
  QPushButton *B98; QPushButton *B89; QPushButton *B88; QPushButton *B87; QPushButton *B86; QPushButton *B85; QPushButton *B84; QPushButton *B83; QPushButton *B82;

  // Boutons apc2
  QPushButton *B64_2; QPushButton *B0_2; QPushButton *B8_2; QPushButton *B16_2; QPushButton *B24_2; QPushButton *B32_2; QPushButton *B40_2; QPushButton *B48_2; QPushButton *B56_2;
  QPushButton *B65_2; QPushButton *B1_2; QPushButton *B9_2; QPushButton *B17_2; QPushButton *B25_2; QPushButton *B33_2; QPushButton *B41_2; QPushButton *B49_2; QPushButton *B57_2;
  QPushButton *B66_2; QPushButton *B2_2; QPushButton *B10_2; QPushButton *B18_2; QPushButton *B26_2; QPushButton *B34_2; QPushButton *B42_2; QPushButton *B50_2; QPushButton *B58_2;
  QPushButton *B67_2; QPushButton *B3_2; QPushButton *B11_2; QPushButton *B19_2; QPushButton *B27_2; QPushButton *B35_2; QPushButton *B43_2; QPushButton *B51_2; QPushButton *B59_2;
  QPushButton *B68_2; QPushButton *B4_2; QPushButton *B12_2; QPushButton *B20_2; QPushButton *B28_2; QPushButton *B36_2; QPushButton *B44_2; QPushButton *B52_2; QPushButton *B60_2;
  QPushButton *B69_2; QPushButton *B5_2; QPushButton *B13_2; QPushButton *B21_2; QPushButton *B29_2; QPushButton *B37_2; QPushButton *B45_2; QPushButton *B53_2; QPushButton *B61_2;
  QPushButton *B70_2; QPushButton *B6_2; QPushButton *B14_2; QPushButton *B22_2; QPushButton *B30_2; QPushButton *B38_2; QPushButton *B46_2; QPushButton *B54_2; QPushButton *B62_2;
  QPushButton *B71_2; QPushButton *B7_2; QPushButton *B15_2; QPushButton *B23_2; QPushButton *B31_2; QPushButton *B39_2; QPushButton *B47_2; QPushButton *B55_2; QPushButton *B63_2;
  QPushButton *B98_2; QPushButton *B89_2; QPushButton *B88_2; QPushButton *B87_2; QPushButton *B86_2; QPushButton *B85_2; QPushButton *B84_2; QPushButton *B83_2; QPushButton *B82_2;

  // Labels dernière colonne
  QLabel *labelRewind; QLabel *labelPlay; QLabel *labelPause;
  QLabel *labelAllSoloOn; QLabel *labelAllSoloOff; QLabel *labelAllVisibleOn; QLabel *labelAllVisibleOff;

  // Connect-Disconnect Midi
  QHBoxLayout *connectLayout1;
    QPushButton *connectMidi1;
    QPushButton *disconnectMidi1;
    QComboBox *midiPorts1;
  QHBoxLayout *connectLayout2;
    QPushButton *connectMidi2;
    QPushButton *disconnectMidi2;
    QComboBox *midiPorts2;
  QPushButton *refreshPorts;
};

#endif // TABMIDI_H
