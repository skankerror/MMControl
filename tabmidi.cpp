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

#include "tabmidi.h"

TabMidi::TabMidi(MyMidiIn *midiIn, MyMidiIn *midiIn2 , QWidget *parent) :
  QWidget(parent),
    m_midiIn(midiIn),
    m_midiIn2(midiIn2)
{
  oscSendS = new OscSend(P_OPACITY, 1, 0, 0);
  oscSendB = new OscSend(M_VISIBLE, 1, true);

  layoutTotal = new QGridLayout;

  labelb9 = new QLabel("Source Rewind"); labelb8 = new QLabel("Source Rate 200%"); labelb7 = new QLabel("Source Rate 100%");
  labelb6 = new QLabel("Source Rate 50%"); labelb5 = new QLabel("Source Rate -100%"); labelb4 = new QLabel("Layer Solo");
  labelb3 = new QLabel("Layer Not Solo"); labelb2 = new QLabel("Layer Visible"); labelb1 = new QLabel("Layer Not Visible");
  labelS = new QLabel("Source Opacity"); labelPid = new QLabel("Source Id"); labelMid = new QLabel("Layer Id");
  layoutTotal->addWidget(labelb9, 0, 0); layoutTotal->addWidget(labelb8, 1, 0);
  layoutTotal->addWidget(labelb7, 2, 0); layoutTotal->addWidget(labelb6, 3, 0);
  layoutTotal->addWidget(labelb5, 4, 0); layoutTotal->addWidget(labelb4, 5, 0);
  layoutTotal->addWidget(labelb3, 6, 0); layoutTotal->addWidget(labelb2, 7, 0);
  layoutTotal->addWidget(labelb1, 8, 0); layoutTotal->addWidget(labelS, 9, 0);
  layoutTotal->addWidget(labelPid, 10, 0); layoutTotal->addWidget(labelMid, 11, 0);

  // APC1
  B64 = new QPushButton; B0 = new QPushButton; B8 = new QPushButton;
  B16 = new QPushButton; B24 = new QPushButton; B32 = new QPushButton;
  B40 = new QPushButton; B48 = new QPushButton; B56 = new QPushButton;
  S1 = new QSlider(Qt::Vertical);
  pID1 = new QSpinBox; pID1->setValue(1); mID1 = new QSpinBox; mID1->setValue(1);
  layoutTotal->addWidget(B56, 0, 1); layoutTotal->addWidget(B48, 1, 1);
  layoutTotal->addWidget(B40, 2, 1); layoutTotal->addWidget(B32, 3, 1);
  layoutTotal->addWidget(B24, 4, 1); layoutTotal->addWidget(B16, 5, 1);
  layoutTotal->addWidget(B8, 6, 1); layoutTotal->addWidget(B0, 7, 1);
  layoutTotal->addWidget(B64, 8, 1); layoutTotal->addWidget(S1, 9, 1);
  layoutTotal->addWidget(pID1, 10, 1); layoutTotal->addWidget(mID1, 11, 1);

  B65 = new QPushButton; B1 = new QPushButton; B9 = new QPushButton;
  B17 = new QPushButton; B25 = new QPushButton; B33 = new QPushButton;
  B41 = new QPushButton; B49 = new QPushButton; B57 = new QPushButton;
  S2 = new QSlider(Qt::Vertical);
  pID2 = new QSpinBox; pID2->setValue(2); mID2 = new QSpinBox; mID2->setValue(2);
  layoutTotal->addWidget(B57, 0, 2); layoutTotal->addWidget(B49, 1, 2);
  layoutTotal->addWidget(B41, 2, 2); layoutTotal->addWidget(B33, 3, 2);
  layoutTotal->addWidget(B25, 4, 2); layoutTotal->addWidget(B17, 5, 2);
  layoutTotal->addWidget(B9, 6, 2); layoutTotal->addWidget(B1, 7, 2);
  layoutTotal->addWidget(B65, 8, 2); layoutTotal->addWidget(S2, 9, 2);
  layoutTotal->addWidget(pID2, 10, 2); layoutTotal->addWidget(mID2, 11, 2);

  B66 = new QPushButton; B2 = new QPushButton; B10 = new QPushButton;
  B18 = new QPushButton; B26 = new QPushButton; B34 = new QPushButton;
  B42 = new QPushButton; B50 = new QPushButton; B58 = new QPushButton;
  S3 = new QSlider(Qt::Vertical);
  pID3 = new QSpinBox; pID3->setValue(3); mID3 = new QSpinBox; mID3->setValue(3);
  layoutTotal->addWidget(B58, 0, 3); layoutTotal->addWidget(B50, 1, 3);
  layoutTotal->addWidget(B42, 2, 3); layoutTotal->addWidget(B34, 3, 3);
  layoutTotal->addWidget(B26, 4, 3); layoutTotal->addWidget(B18, 5, 3);
  layoutTotal->addWidget(B10, 6, 3); layoutTotal->addWidget(B2, 7, 3);
  layoutTotal->addWidget(B66, 8, 3); layoutTotal->addWidget(S3, 9, 3);
  layoutTotal->addWidget(pID3, 10, 3); layoutTotal->addWidget(mID3, 11, 3);

  B67 = new QPushButton; B3 = new QPushButton; B11 = new QPushButton;
  B19 = new QPushButton; B27 = new QPushButton; B35 = new QPushButton;
  B43 = new QPushButton; B51 = new QPushButton; B59 = new QPushButton;
  S4 = new QSlider(Qt::Vertical);
  pID4 = new QSpinBox; pID4->setValue(4); mID4 = new QSpinBox; mID4->setValue(4);
  layoutTotal->addWidget(B59, 0, 4); layoutTotal->addWidget(B51, 1, 4);
  layoutTotal->addWidget(B43, 2, 4); layoutTotal->addWidget(B35, 3, 4);
  layoutTotal->addWidget(B27, 4, 4); layoutTotal->addWidget(B19, 5, 4);
  layoutTotal->addWidget(B11, 6, 4); layoutTotal->addWidget(B3, 7, 4);
  layoutTotal->addWidget(B67, 8, 4); layoutTotal->addWidget(S4, 9, 4);
  layoutTotal->addWidget(pID4, 10, 4); layoutTotal->addWidget(mID4, 11, 4);

  B68 = new QPushButton; B4 = new QPushButton; B12 = new QPushButton;
  B20 = new QPushButton; B28 = new QPushButton; B36 = new QPushButton;
  B44 = new QPushButton; B52 = new QPushButton; B60 = new QPushButton;
  S5 = new QSlider(Qt::Vertical);
  pID5 = new QSpinBox; pID5->setValue(5); mID5 = new QSpinBox; mID5->setValue(5);
  layoutTotal->addWidget(B60, 0, 5); layoutTotal->addWidget(B52, 1, 5);
  layoutTotal->addWidget(B44, 2, 5); layoutTotal->addWidget(B36, 3, 5);
  layoutTotal->addWidget(B28, 4, 5); layoutTotal->addWidget(B20, 5, 5);
  layoutTotal->addWidget(B12, 6, 5); layoutTotal->addWidget(B4, 7, 5);
  layoutTotal->addWidget(B68, 8, 5); layoutTotal->addWidget(S5, 9, 5);
  layoutTotal->addWidget(pID5, 10, 5); layoutTotal->addWidget(mID5, 11, 5);

  B69 = new QPushButton; B5 = new QPushButton; B13 = new QPushButton;
  B21 = new QPushButton; B29 = new QPushButton; B37 = new QPushButton;
  B45 = new QPushButton; B53 = new QPushButton; B61 = new QPushButton;
  S6 = new QSlider(Qt::Vertical);
  pID6 = new QSpinBox; pID6->setValue(6); mID6 = new QSpinBox; mID6->setValue(6);
  layoutTotal->addWidget(B61, 0, 6); layoutTotal->addWidget(B53, 1, 6);
  layoutTotal->addWidget(B45, 2, 6); layoutTotal->addWidget(B37, 3, 6);
  layoutTotal->addWidget(B29, 4, 6); layoutTotal->addWidget(B21, 5, 6);
  layoutTotal->addWidget(B13, 6, 6); layoutTotal->addWidget(B5, 7, 6);
  layoutTotal->addWidget(B69, 8, 6); layoutTotal->addWidget(S6, 9, 6);
  layoutTotal->addWidget(pID6, 10, 6); layoutTotal->addWidget(mID6, 11, 6);

  B70 = new QPushButton; B6 = new QPushButton; B14 = new QPushButton;
  B22 = new QPushButton; B30 = new QPushButton; B38 = new QPushButton;
  B46 = new QPushButton; B54 = new QPushButton; B62 = new QPushButton;
  S7 = new QSlider(Qt::Vertical);
  pID7 = new QSpinBox; pID7->setValue(7); mID7 = new QSpinBox; mID7->setValue(7);
  layoutTotal->addWidget(B62, 0, 7); layoutTotal->addWidget(B54, 1, 7);
  layoutTotal->addWidget(B46, 2, 7); layoutTotal->addWidget(B38, 3, 7);
  layoutTotal->addWidget(B30, 4, 7); layoutTotal->addWidget(B22, 5, 7);
  layoutTotal->addWidget(B14, 6, 7); layoutTotal->addWidget(B6, 7, 7);
  layoutTotal->addWidget(B70, 8, 7); layoutTotal->addWidget(S7, 9, 7);
  layoutTotal->addWidget(pID7, 10, 7); layoutTotal->addWidget(mID7, 11, 7);

  B71 = new QPushButton; B7 = new QPushButton; B15 = new QPushButton;
  B23 = new QPushButton; B31 = new QPushButton; B39 = new QPushButton;
  B47 = new QPushButton; B55 = new QPushButton; B63 = new QPushButton;
  S8 = new QSlider(Qt::Vertical);
  pID8 = new QSpinBox; pID8->setValue(8); mID8 = new QSpinBox; mID8->setValue(8);
  layoutTotal->addWidget(B63, 0, 8); layoutTotal->addWidget(B55, 1, 8);
  layoutTotal->addWidget(B47, 2, 8); layoutTotal->addWidget(B39, 3, 8);
  layoutTotal->addWidget(B31, 4, 8); layoutTotal->addWidget(B23, 5, 8);
  layoutTotal->addWidget(B15, 6, 8); layoutTotal->addWidget(B7, 7, 8);
  layoutTotal->addWidget(B71, 8, 8); layoutTotal->addWidget(S8, 9, 8);
  layoutTotal->addWidget(pID8, 10, 8); layoutTotal->addWidget(mID8, 11, 8);

  B98 = new QPushButton; B89 = new QPushButton; B88 = new QPushButton;
  B87 = new QPushButton; B86 = new QPushButton; B85 = new QPushButton;
  B84 = new QPushButton; B83 = new QPushButton; B82 = new QPushButton;
  S9 = new QSlider(Qt::Vertical);
  pID9 = new QSpinBox; pID9->setValue(9); mID9 = new QSpinBox; mID9->setValue(9);
  layoutTotal->addWidget(B82, 0, 9); layoutTotal->addWidget(B83, 1, 9);
  layoutTotal->addWidget(B84, 2, 9); layoutTotal->addWidget(B85, 3, 9);
  layoutTotal->addWidget(B86, 4, 9); layoutTotal->addWidget(B87, 5, 9);
  layoutTotal->addWidget(B88, 6, 9); layoutTotal->addWidget(B89, 7, 9);
  layoutTotal->addWidget(B98, 8, 9); layoutTotal->addWidget(S9, 9, 9);
  layoutTotal->addWidget(pID9, 10, 9); layoutTotal->addWidget(mID9, 11, 9);

  // align sliders APC1
  layoutTotal->setAlignment(S1, Qt::AlignHCenter); layoutTotal->setAlignment(S2, Qt::AlignHCenter);
  layoutTotal->setAlignment(S3, Qt::AlignHCenter); layoutTotal->setAlignment(S4, Qt::AlignHCenter);
  layoutTotal->setAlignment(S5, Qt::AlignHCenter); layoutTotal->setAlignment(S6, Qt::AlignHCenter);
  layoutTotal->setAlignment(S7, Qt::AlignHCenter); layoutTotal->setAlignment(S8, Qt::AlignHCenter);
  layoutTotal->setAlignment(S9, Qt::AlignHCenter);

  layoutTotal->setColumnMinimumWidth(10, 10); // Pour avoir une séparation entre les 2 apcmini col 10

  // APC2
  B64_2 = new QPushButton; B0_2 = new QPushButton; B8_2 = new QPushButton;
  B16_2 = new QPushButton; B24_2 = new QPushButton; B32_2 = new QPushButton;
  B40_2 = new QPushButton; B48_2 = new QPushButton; B56_2 = new QPushButton;
  S10 = new QSlider(Qt::Vertical);
  pID10 = new QSpinBox; pID10->setValue(10); mID10 = new QSpinBox; mID10->setValue(10);
  layoutTotal->addWidget(B56_2, 0, 11); layoutTotal->addWidget(B48_2, 1, 11);
  layoutTotal->addWidget(B40_2, 2, 11); layoutTotal->addWidget(B32_2, 3, 11);
  layoutTotal->addWidget(B24_2, 4, 11); layoutTotal->addWidget(B16_2, 5, 11);
  layoutTotal->addWidget(B8_2, 6, 11); layoutTotal->addWidget(B0_2, 7, 11);
  layoutTotal->addWidget(B64_2, 8, 11); layoutTotal->addWidget(S10, 9, 11);
  layoutTotal->addWidget(pID10, 10, 11); layoutTotal->addWidget(mID10, 11, 11);

  B65_2 = new QPushButton; B1_2 = new QPushButton; B9_2 = new QPushButton;
  B17_2 = new QPushButton; B25_2 = new QPushButton; B33_2 = new QPushButton;
  B41_2 = new QPushButton; B49_2 = new QPushButton; B57_2 = new QPushButton;
  S11 = new QSlider(Qt::Vertical);
  pID11 = new QSpinBox; pID11->setValue(11); mID11 = new QSpinBox; mID11->setValue(11);
  layoutTotal->addWidget(B57_2, 0, 12); layoutTotal->addWidget(B49_2, 1, 12);
  layoutTotal->addWidget(B41_2, 2, 12); layoutTotal->addWidget(B33_2, 3, 12);
  layoutTotal->addWidget(B25_2, 4, 12); layoutTotal->addWidget(B17_2, 5, 12);
  layoutTotal->addWidget(B9_2, 6, 12); layoutTotal->addWidget(B1_2, 7, 12);
  layoutTotal->addWidget(B65_2, 8, 12); layoutTotal->addWidget(S11, 9, 12);
  layoutTotal->addWidget(pID11, 10, 12); layoutTotal->addWidget(mID11, 11, 12);

  B66_2 = new QPushButton; B2_2 = new QPushButton; B10_2 = new QPushButton;
  B18_2 = new QPushButton; B26_2 = new QPushButton; B34_2 = new QPushButton;
  B42_2 = new QPushButton; B50_2 = new QPushButton; B58_2 = new QPushButton;
  S12 = new QSlider(Qt::Vertical);
  pID12 = new QSpinBox; pID12->setValue(12); mID12 = new QSpinBox; mID12->setValue(12);
  layoutTotal->addWidget(B58_2, 0, 13); layoutTotal->addWidget(B50_2, 1, 13);
  layoutTotal->addWidget(B42_2, 2, 13); layoutTotal->addWidget(B34_2, 3, 13);
  layoutTotal->addWidget(B26_2, 4, 13); layoutTotal->addWidget(B18_2, 5, 13);
  layoutTotal->addWidget(B10_2, 6, 13); layoutTotal->addWidget(B2_2, 7, 13);
  layoutTotal->addWidget(B66_2, 8, 13); layoutTotal->addWidget(S12, 9, 13);
  layoutTotal->addWidget(pID12, 10, 13); layoutTotal->addWidget(mID12, 11, 13);

  B67_2 = new QPushButton; B3_2 = new QPushButton; B11_2 = new QPushButton;
  B19_2 = new QPushButton; B27_2 = new QPushButton; B35_2 = new QPushButton;
  B43_2 = new QPushButton; B51_2 = new QPushButton; B59_2 = new QPushButton;
  S13 = new QSlider(Qt::Vertical);
  pID13 = new QSpinBox; pID13->setValue(13); mID13 = new QSpinBox; mID13->setValue(13);
  layoutTotal->addWidget(B59_2, 0, 14); layoutTotal->addWidget(B51_2, 1, 14);
  layoutTotal->addWidget(B43_2, 2, 14); layoutTotal->addWidget(B35_2, 3, 14);
  layoutTotal->addWidget(B27_2, 4, 14); layoutTotal->addWidget(B19_2, 5, 14);
  layoutTotal->addWidget(B11_2, 6, 14); layoutTotal->addWidget(B3_2, 7, 14);
  layoutTotal->addWidget(B67_2, 8, 14); layoutTotal->addWidget(S13, 9, 14);
  layoutTotal->addWidget(pID13, 10, 14); layoutTotal->addWidget(mID13, 11, 14);

  B68_2 = new QPushButton; B4_2 = new QPushButton; B12_2 = new QPushButton;
  B20_2 = new QPushButton; B28_2 = new QPushButton; B36_2 = new QPushButton;
  B44_2 = new QPushButton; B52_2 = new QPushButton; B60_2 = new QPushButton;
  S14 = new QSlider(Qt::Vertical);
  pID14 = new QSpinBox; pID14->setValue(14); mID14 = new QSpinBox; mID14->setValue(14);
  layoutTotal->addWidget(B60_2, 0, 15); layoutTotal->addWidget(B52_2, 1, 15);
  layoutTotal->addWidget(B44_2, 2, 15); layoutTotal->addWidget(B36_2, 3, 15);
  layoutTotal->addWidget(B28_2, 4, 15); layoutTotal->addWidget(B20_2, 5, 15);
  layoutTotal->addWidget(B12_2, 6, 15); layoutTotal->addWidget(B4_2, 7, 15);
  layoutTotal->addWidget(B68_2, 8, 15); layoutTotal->addWidget(S14, 9, 15);
  layoutTotal->addWidget(pID14, 10, 15); layoutTotal->addWidget(mID14, 11, 15);

  B69_2 = new QPushButton; B5_2 = new QPushButton; B13_2 = new QPushButton;
  B21_2 = new QPushButton; B29_2 = new QPushButton; B37_2 = new QPushButton;
  B45_2 = new QPushButton; B53_2 = new QPushButton; B61_2 = new QPushButton;
  S15 = new QSlider(Qt::Vertical);
  pID15 = new QSpinBox; pID15->setValue(15); mID15 = new QSpinBox; mID15->setValue(15);
  layoutTotal->addWidget(B61_2, 0, 16); layoutTotal->addWidget(B53_2, 1, 16);
  layoutTotal->addWidget(B45_2, 2, 16); layoutTotal->addWidget(B37_2, 3, 16);
  layoutTotal->addWidget(B29_2, 4, 16); layoutTotal->addWidget(B21_2, 5, 16);
  layoutTotal->addWidget(B13_2, 6, 16); layoutTotal->addWidget(B5_2, 7, 16);
  layoutTotal->addWidget(B69_2, 8, 16); layoutTotal->addWidget(S15, 9, 16);
  layoutTotal->addWidget(pID15, 10, 16); layoutTotal->addWidget(mID15, 11, 16);

  B70_2 = new QPushButton; B6_2 = new QPushButton; B14_2 = new QPushButton;
  B22_2 = new QPushButton; B30_2 = new QPushButton; B38_2 = new QPushButton;
  B46_2 = new QPushButton; B54_2 = new QPushButton; B62_2 = new QPushButton;
  S16 = new QSlider(Qt::Vertical);
  pID16 = new QSpinBox; pID16->setValue(16); mID16 = new QSpinBox; mID16->setValue(16);
  layoutTotal->addWidget(B62_2, 0, 17); layoutTotal->addWidget(B54_2, 1, 17);
  layoutTotal->addWidget(B46_2, 2, 17); layoutTotal->addWidget(B38_2, 3, 17);
  layoutTotal->addWidget(B30_2, 4, 17); layoutTotal->addWidget(B22_2, 5, 17);
  layoutTotal->addWidget(B14_2, 6, 17); layoutTotal->addWidget(B6_2, 7, 17);
  layoutTotal->addWidget(B70_2, 8, 17); layoutTotal->addWidget(S16, 9, 17);
  layoutTotal->addWidget(pID16, 10, 17); layoutTotal->addWidget(mID16, 11, 17);

  B71_2 = new QPushButton; B7_2 = new QPushButton; B15_2 = new QPushButton;
  B23_2 = new QPushButton; B31_2 = new QPushButton; B39_2 = new QPushButton;
  B47_2 = new QPushButton; B55_2 = new QPushButton; B63_2 = new QPushButton;
  S17 = new QSlider(Qt::Vertical);
  pID17 = new QSpinBox; pID17->setValue(17); mID17 = new QSpinBox; mID17->setValue(17);
  layoutTotal->addWidget(B63_2, 0, 18); layoutTotal->addWidget(B55_2, 1, 18);
  layoutTotal->addWidget(B47_2, 2, 18); layoutTotal->addWidget(B39_2, 3, 18);
  layoutTotal->addWidget(B31_2, 4, 18); layoutTotal->addWidget(B23_2, 5, 18);
  layoutTotal->addWidget(B15_2, 6, 18); layoutTotal->addWidget(B7_2, 7, 18);
  layoutTotal->addWidget(B71_2, 8, 18); layoutTotal->addWidget(S17, 9, 18);
  layoutTotal->addWidget(pID17, 10, 18); layoutTotal->addWidget(mID17, 11, 18);

  B98_2 = new QPushButton; B89_2 = new QPushButton; B88_2 = new QPushButton;
  B87_2 = new QPushButton; B86_2 = new QPushButton; B85_2 = new QPushButton;
  B84_2 = new QPushButton; B83_2 = new QPushButton; B82_2 = new QPushButton;
  S18 = new QSlider(Qt::Vertical);
  pID18 = new QSpinBox; pID18->setValue(18); mID18 = new QSpinBox; mID18->setValue(18);
  layoutTotal->addWidget(B82_2, 0, 19); layoutTotal->addWidget(B83_2, 1, 19);
  layoutTotal->addWidget(B84_2, 2, 19); layoutTotal->addWidget(B85_2, 3, 19);
  layoutTotal->addWidget(B86_2, 4, 19); layoutTotal->addWidget(B87_2, 5, 19);
  layoutTotal->addWidget(B88_2, 6, 19); layoutTotal->addWidget(B89_2, 7, 19);
  layoutTotal->addWidget(B98_2, 8, 19); layoutTotal->addWidget(S18, 9, 19);
  layoutTotal->addWidget(pID18, 10, 19); layoutTotal->addWidget(mID18, 11, 19);

  // align sliders APC2
  layoutTotal->setAlignment(S10, Qt::AlignHCenter); layoutTotal->setAlignment(S11, Qt::AlignHCenter);
  layoutTotal->setAlignment(S12, Qt::AlignHCenter); layoutTotal->setAlignment(S13, Qt::AlignHCenter);
  layoutTotal->setAlignment(S14, Qt::AlignHCenter); layoutTotal->setAlignment(S15, Qt::AlignHCenter);
  layoutTotal->setAlignment(S16, Qt::AlignHCenter); layoutTotal->setAlignment(S17, Qt::AlignHCenter);
  layoutTotal->setAlignment(S18, Qt::AlignHCenter);  this->setLayout(layoutTotal);

  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::gray);
  setAutoFillBackground(true);
  setPalette(pal);

  // connect midiIn1
  connect(m_midiIn, SIGNAL(sigMidiCtrlChanged(int, float)), this, SLOT(receiveMidiCtrl(int,float)));
  connect(m_midiIn, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote(int)));
  // connect midiIn2
  connect(m_midiIn2, SIGNAL(sigMidiCtrlChanged(int, float)), this, SLOT(receiveMidiCtrl2(int,float)));
  connect(m_midiIn2, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote2(int)));

  //connections des sliders
  { //APC1
    connect(this->S1, SIGNAL(valueChanged(int)), this, SLOT(sendOscS1(int)));
    connect(this->S2, SIGNAL(valueChanged(int)), this, SLOT(sendOscS2(int)));
    connect(this->S3, SIGNAL(valueChanged(int)), this, SLOT(sendOscS3(int)));
    connect(this->S4, SIGNAL(valueChanged(int)), this, SLOT(sendOscS4(int)));
    connect(this->S5, SIGNAL(valueChanged(int)), this, SLOT(sendOscS5(int)));
    connect(this->S6, SIGNAL(valueChanged(int)), this, SLOT(sendOscS6(int)));
    connect(this->S7, SIGNAL(valueChanged(int)), this, SLOT(sendOscS7(int)));
    connect(this->S8, SIGNAL(valueChanged(int)), this, SLOT(sendOscS8(int)));
    connect(this->S9, SIGNAL(valueChanged(int)), this, SLOT(sendOscS9(int)));
    //APC2
    connect(this->S10, SIGNAL(valueChanged(int)), this, SLOT(sendOscS10(int)));
    connect(this->S11, SIGNAL(valueChanged(int)), this, SLOT(sendOscS11(int)));
    connect(this->S12, SIGNAL(valueChanged(int)), this, SLOT(sendOscS12(int)));
    connect(this->S13, SIGNAL(valueChanged(int)), this, SLOT(sendOscS13(int)));
    connect(this->S14, SIGNAL(valueChanged(int)), this, SLOT(sendOscS14(int)));
    connect(this->S15, SIGNAL(valueChanged(int)), this, SLOT(sendOscS15(int)));
    connect(this->S16, SIGNAL(valueChanged(int)), this, SLOT(sendOscS16(int)));
    connect(this->S17, SIGNAL(valueChanged(int)), this, SLOT(sendOscS17(int)));
    connect(this->S18, SIGNAL(valueChanged(int)), this, SLOT(sendOscS18(int)));}

  // connections de tous les boutons APC1
  {connect(this->B64, SIGNAL(clicked()), this, SLOT(sendOscAPCB64()));
    connect(this->B65, SIGNAL(clicked()), this, SLOT(sendOscAPCB65()));
    connect(this->B66, SIGNAL(clicked()), this, SLOT(sendOscAPCB66()));
    connect(this->B67, SIGNAL(clicked()), this, SLOT(sendOscAPCB67()));
    connect(this->B68, SIGNAL(clicked()), this, SLOT(sendOscAPCB68()));
    connect(this->B69, SIGNAL(clicked()), this, SLOT(sendOscAPCB69()));
    connect(this->B70, SIGNAL(clicked()), this, SLOT(sendOscAPCB70()));
    connect(this->B71, SIGNAL(clicked()), this, SLOT(sendOscAPCB71()));
    connect(this->B98, SIGNAL(clicked()), this, SLOT(sendOscAPCB98()));

    connect(this->B0, SIGNAL(clicked()), this, SLOT(sendOscAPCB0()));
    connect(this->B1, SIGNAL(clicked()), this, SLOT(sendOscAPCB1()));
    connect(this->B2, SIGNAL(clicked()), this, SLOT(sendOscAPCB2()));
    connect(this->B3, SIGNAL(clicked()), this, SLOT(sendOscAPCB3()));
    connect(this->B4, SIGNAL(clicked()), this, SLOT(sendOscAPCB4()));
    connect(this->B5, SIGNAL(clicked()), this, SLOT(sendOscAPCB5()));
    connect(this->B6, SIGNAL(clicked()), this, SLOT(sendOscAPCB6()));
    connect(this->B7, SIGNAL(clicked()), this, SLOT(sendOscAPCB7()));
    connect(this->B89, SIGNAL(clicked()), this, SLOT(sendOscAPCB89()));

    connect(this->B8, SIGNAL(clicked()), this, SLOT(sendOscAPCB8()));
    connect(this->B9, SIGNAL(clicked()), this, SLOT(sendOscAPCB9()));
    connect(this->B10, SIGNAL(clicked()), this, SLOT(sendOscAPCB10()));
    connect(this->B11, SIGNAL(clicked()), this, SLOT(sendOscAPCB11()));
    connect(this->B12, SIGNAL(clicked()), this, SLOT(sendOscAPCB12()));
    connect(this->B13, SIGNAL(clicked()), this, SLOT(sendOscAPCB13()));
    connect(this->B14, SIGNAL(clicked()), this, SLOT(sendOscAPCB14()));
    connect(this->B15, SIGNAL(clicked()), this, SLOT(sendOscAPCB15()));
    connect(this->B88, SIGNAL(clicked()), this, SLOT(sendOscAPCB88()));

    connect(this->B16, SIGNAL(clicked()), this, SLOT(sendOscAPCB16()));
    connect(this->B17, SIGNAL(clicked()), this, SLOT(sendOscAPCB17()));
    connect(this->B18, SIGNAL(clicked()), this, SLOT(sendOscAPCB18()));
    connect(this->B19, SIGNAL(clicked()), this, SLOT(sendOscAPCB19()));
    connect(this->B20, SIGNAL(clicked()), this, SLOT(sendOscAPCB20()));
    connect(this->B21, SIGNAL(clicked()), this, SLOT(sendOscAPCB21()));
    connect(this->B22, SIGNAL(clicked()), this, SLOT(sendOscAPCB22()));
    connect(this->B23, SIGNAL(clicked()), this, SLOT(sendOscAPCB23()));
    connect(this->B87, SIGNAL(clicked()), this, SLOT(sendOscAPCB87()));

    connect(this->B24, SIGNAL(clicked()), this, SLOT(sendOscAPCB24()));
    connect(this->B25, SIGNAL(clicked()), this, SLOT(sendOscAPCB25()));
    connect(this->B26, SIGNAL(clicked()), this, SLOT(sendOscAPCB26()));
    connect(this->B27, SIGNAL(clicked()), this, SLOT(sendOscAPCB27()));
    connect(this->B28, SIGNAL(clicked()), this, SLOT(sendOscAPCB28()));
    connect(this->B29, SIGNAL(clicked()), this, SLOT(sendOscAPCB29()));
    connect(this->B30, SIGNAL(clicked()), this, SLOT(sendOscAPCB30()));
    connect(this->B31, SIGNAL(clicked()), this, SLOT(sendOscAPCB31()));
    connect(this->B86, SIGNAL(clicked()), this, SLOT(sendOscAPCB86()));

    connect(this->B32, SIGNAL(clicked()), this, SLOT(sendOscAPCB32()));
    connect(this->B33, SIGNAL(clicked()), this, SLOT(sendOscAPCB33()));
    connect(this->B34, SIGNAL(clicked()), this, SLOT(sendOscAPCB34()));
    connect(this->B35, SIGNAL(clicked()), this, SLOT(sendOscAPCB35()));
    connect(this->B36, SIGNAL(clicked()), this, SLOT(sendOscAPCB36()));
    connect(this->B37, SIGNAL(clicked()), this, SLOT(sendOscAPCB37()));
    connect(this->B38, SIGNAL(clicked()), this, SLOT(sendOscAPCB38()));
    connect(this->B39, SIGNAL(clicked()), this, SLOT(sendOscAPCB39()));
    connect(this->B85, SIGNAL(clicked()), this, SLOT(sendOscAPCB85()));

    connect(this->B40, SIGNAL(clicked()), this, SLOT(sendOscAPCB40()));
    connect(this->B41, SIGNAL(clicked()), this, SLOT(sendOscAPCB41()));
    connect(this->B42, SIGNAL(clicked()), this, SLOT(sendOscAPCB42()));
    connect(this->B43, SIGNAL(clicked()), this, SLOT(sendOscAPCB43()));
    connect(this->B44, SIGNAL(clicked()), this, SLOT(sendOscAPCB44()));
    connect(this->B45, SIGNAL(clicked()), this, SLOT(sendOscAPCB45()));
    connect(this->B46, SIGNAL(clicked()), this, SLOT(sendOscAPCB46()));
    connect(this->B47, SIGNAL(clicked()), this, SLOT(sendOscAPCB47()));
    connect(this->B84, SIGNAL(clicked()), this, SLOT(sendOscAPCB84()));

    connect(this->B48, SIGNAL(clicked()), this, SLOT(sendOscAPCB48()));
    connect(this->B49, SIGNAL(clicked()), this, SLOT(sendOscAPCB49()));
    connect(this->B50, SIGNAL(clicked()), this, SLOT(sendOscAPCB50()));
    connect(this->B51, SIGNAL(clicked()), this, SLOT(sendOscAPCB51()));
    connect(this->B52, SIGNAL(clicked()), this, SLOT(sendOscAPCB52()));
    connect(this->B53, SIGNAL(clicked()), this, SLOT(sendOscAPCB53()));
    connect(this->B54, SIGNAL(clicked()), this, SLOT(sendOscAPCB54()));
    connect(this->B55, SIGNAL(clicked()), this, SLOT(sendOscAPCB55()));
    connect(this->B83, SIGNAL(clicked()), this, SLOT(sendOscAPCB83()));

    connect(this->B56, SIGNAL(clicked()), this, SLOT(sendOscAPCB56()));
    connect(this->B57, SIGNAL(clicked()), this, SLOT(sendOscAPCB57()));
    connect(this->B58, SIGNAL(clicked()), this, SLOT(sendOscAPCB58()));
    connect(this->B59, SIGNAL(clicked()), this, SLOT(sendOscAPCB59()));
    connect(this->B60, SIGNAL(clicked()), this, SLOT(sendOscAPCB60()));
    connect(this->B61, SIGNAL(clicked()), this, SLOT(sendOscAPCB61()));
    connect(this->B62, SIGNAL(clicked()), this, SLOT(sendOscAPCB62()));
    connect(this->B63, SIGNAL(clicked()), this, SLOT(sendOscAPCB63()));
    connect(this->B82, SIGNAL(clicked()), this, SLOT(sendOscAPCB82()));}

  // connections de tous les boutons APC2
  {connect(this->B64_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB64_2()));
    connect(this->B65_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB65_2()));
    connect(this->B66_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB66_2()));
    connect(this->B67_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB67_2()));
    connect(this->B68_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB68_2()));
    connect(this->B69_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB69_2()));
    connect(this->B70_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB70_2()));
    connect(this->B71_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB71_2()));
    connect(this->B98_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB98_2()));

    connect(this->B0_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB0_2()));
    connect(this->B1_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB1_2()));
    connect(this->B2_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB2_2()));
    connect(this->B3_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB3_2()));
    connect(this->B4_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB4_2()));
    connect(this->B5_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB5_2()));
    connect(this->B6_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB6_2()));
    connect(this->B7_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB7_2()));
    connect(this->B89_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB89_2()));

    connect(this->B8_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB8_2()));
    connect(this->B9_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB9_2()));
    connect(this->B10_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB10_2()));
    connect(this->B11_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB11_2()));
    connect(this->B12_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB12_2()));
    connect(this->B13_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB13_2()));
    connect(this->B14_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB14_2()));
    connect(this->B15_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB15_2()));
    connect(this->B88_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB88_2()));

    connect(this->B16_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB16_2()));
    connect(this->B17_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB17_2()));
    connect(this->B18_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB18_2()));
    connect(this->B19_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB19_2()));
    connect(this->B20_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB20_2()));
    connect(this->B21_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB21_2()));
    connect(this->B22_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB22_2()));
    connect(this->B23_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB23_2()));
    connect(this->B87_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB87_2()));

    connect(this->B24_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB24_2()));
    connect(this->B25_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB25_2()));
    connect(this->B26_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB26_2()));
    connect(this->B27_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB27_2()));
    connect(this->B28_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB28_2()));
    connect(this->B29_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB29_2()));
    connect(this->B30_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB30_2()));
    connect(this->B31_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB31_2()));
    connect(this->B86_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB86_2()));

    connect(this->B32_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB32_2()));
    connect(this->B33_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB33_2()));
    connect(this->B34_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB34_2()));
    connect(this->B35_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB35_2()));
    connect(this->B36_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB36_2()));
    connect(this->B37_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB37_2()));
    connect(this->B38_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB38_2()));
    connect(this->B39_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB39_2()));
    connect(this->B85_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB85_2()));

    connect(this->B40_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB40_2()));
    connect(this->B41_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB41_2()));
    connect(this->B42_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB42_2()));
    connect(this->B43_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB43_2()));
    connect(this->B44_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB44_2()));
    connect(this->B45_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB45_2()));
    connect(this->B46_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB46_2()));
    connect(this->B47_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB47_2()));
    connect(this->B84_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB84_2()));

    connect(this->B48_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB48_2()));
    connect(this->B49_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB49_2()));
    connect(this->B50_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB50_2()));
    connect(this->B51_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB51_2()));
    connect(this->B52_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB52_2()));
    connect(this->B53_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB53_2()));
    connect(this->B54_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB54_2()));
    connect(this->B55_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB55_2()));
    connect(this->B83_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB83_2()));

    connect(this->B56_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB56_2()));
    connect(this->B57_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB57_2()));
    connect(this->B58_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB58_2()));
    connect(this->B59_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB59_2()));
    connect(this->B60_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB60_2()));
    connect(this->B61_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB61_2()));
    connect(this->B62_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB62_2()));
    connect(this->B63_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB63_2()));
    connect(this->B82_2, SIGNAL(clicked()), this, SLOT(sendOscAPCB82_2()));}
}


void TabMidi::receiveMidiCtrl(int unID, float uneOpacite) // APC1
{

  switch(unID)
  {
  case 1: this->S1->setValue((int)(uneOpacite*100)); break; case 2: this->S2->setValue((int)(uneOpacite*100)); break;
  case 3: this->S3->setValue((int)(uneOpacite*100)); break; case 4: this->S4->setValue((int)(uneOpacite*100)); break;
  case 5: this->S5->setValue((int)(uneOpacite*100)); break; case 6: this->S6->setValue((int)(uneOpacite*100)); break;
  case 7: this->S7->setValue((int)(uneOpacite*100)); break; case 8: this->S8->setValue((int)(uneOpacite*100)); break;
  case 9: this->S9->setValue((int)(uneOpacite*100)); break; default : break;
  }
}

void TabMidi::receiveMidiCtrl2(int unID, float uneOpacite) // APC2
{

  switch(unID)
  {
  case 1: this->S10->setValue((int)(uneOpacite*100)); break; case 2: this->S11->setValue((int)(uneOpacite*100)); break;
  case 3: this->S12->setValue((int)(uneOpacite*100)); break; case 4: this->S13->setValue((int)(uneOpacite*100)); break;
  case 5: this->S14->setValue((int)(uneOpacite*100)); break; case 6: this->S15->setValue((int)(uneOpacite*100)); break;
  case 7: this->S16->setValue((int)(uneOpacite*100)); break; case 8: this->S17->setValue((int)(uneOpacite*100)); break;
  case 9: this->S18->setValue((int)(uneOpacite*100)); break; default : break;
  }
}
// APC1
void TabMidi::sendOscS1(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID1->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS2(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID2->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS3(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID3->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS4(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID4->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS5(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID5->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS6(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID6->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS7(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID7->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS8(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID8->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS9(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID9->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}

// APC2
void TabMidi::sendOscS10(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID10->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS11(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID11->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS12(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID12->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS13(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID13->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS14(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID14->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS15(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID15->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS16(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID16->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS17(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID17->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}
void TabMidi::sendOscS18(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID18->value(); oscSendS->m_p_opacity = uneOpacite; oscSendS->ExecuteSend();
}

void TabMidi::receiveMidiNote(int unBouton) // APC1
{

  switch (unBouton)
  {
  // rangée 9 au dessus des sliders paint/color
  case 64: this->B64->animateClick(); break;
  case 65: this->B65->animateClick(); break;
  case 66: this->B66->animateClick(); break;
  case 67: this->B67->animateClick(); break;
  case 68: this->B68->animateClick(); break;
  case 69: this->B69->animateClick(); break;
  case 70: this->B70->animateClick(); break;
  case 71: this->B71->animateClick(); break;
  case 98: this->B98->animateClick(); break;

    // rangée 8 paint/rate
  case 0: this->B0->animateClick(); break;
  case 1: this->B1->animateClick(); break;
  case 2: this->B2->animateClick(); break;
  case 3: this->B3->animateClick(); break;
  case 4: this->B4->animateClick(); break;
  case 5: this->B5->animateClick(); break;
  case 6: this->B6->animateClick(); break;
  case 7: this->B7->animateClick(); break;
  case 89: this->B89->animateClick(); break;

    //rangée 7 mapping/solo off
  case 8: this->B8->animateClick(); break;
  case 9: this->B9->animateClick(); break;
  case 10: this->B10->animateClick(); break;
  case 11: this->B11->animateClick(); break;
  case 12: this->B12->animateClick(); break;
  case 13: this->B13->animateClick(); break;
  case 14: this->B14->animateClick(); break;
  case 15: this->B15->animateClick(); break;
  case 88: this->B88->animateClick(); break;

    // rangée 6 mapping/solo on
  case 16: this->B16->animateClick(); break;
  case 17: this->B17->animateClick(); break;
  case 18: this->B18->animateClick(); break;
  case 19: this->B19->animateClick(); break;
  case 20: this->B20->animateClick(); break;
  case 21: this->B21->animateClick(); break;
  case 22: this->B22->animateClick(); break;
  case 23: this->B23->animateClick(); break;
  case 87: this->B87->animateClick(); break;

    // rangée 5 mapping/visible off
  case 24: this->B24->animateClick(); break;
  case 25: this->B25->animateClick(); break;
  case 26: this->B26->animateClick(); break;
  case 27: this->B27->animateClick(); break;
  case 28: this->B28->animateClick(); break;
  case 29: this->B29->animateClick(); break;
  case 30: this->B30->animateClick(); break;
  case 31: this->B31->animateClick(); break;
  case 86: this->B86->animateClick(); break;

    // rangée 4 mapping/visible on
  case 32: this->B32->animateClick(); break;
  case 33: this->B33->animateClick(); break;
  case 34: this->B34->animateClick(); break;
  case 35: this->B35->animateClick(); break;
  case 36: this->B36->animateClick(); break;
  case 37: this->B37->animateClick(); break;
  case 38: this->B38->animateClick(); break;
  case 39: this->B39->animateClick(); break;
  case 85: this->B85->animateClick(); break;

    // rangée 3 paint/uri/ previous
  case 40: this->B40->animateClick(); break;
  case 41: this->B41->animateClick(); break;
  case 42: this->B42->animateClick(); break;
  case 43: this->B43->animateClick(); break;
  case 44: this->B44->animateClick(); break;
  case 45: this->B45->animateClick(); break;
  case 46: this->B46->animateClick(); break;
  case 47: this->B47->animateClick(); break;
  case 84: this->B84->animateClick(); break;

    // rangée 2 paint/uri next
  case 48: this->B48->animateClick(); break;
  case 49: this->B49->animateClick(); break;
  case 50: this->B50->animateClick(); break;
  case 51: this->B51->animateClick(); break;
  case 52: this->B52->animateClick(); break;
  case 53: this->B53->animateClick(); break;
  case 54: this->B54->animateClick(); break;
  case 55: this->B55->animateClick(); break;
  case 83: this->B83->animateClick(); break;

    // rangée 1 paint/uri uri
  case 56: this->B56->animateClick(); break;
  case 57: this->B57->animateClick(); break;
  case 58: this->B58->animateClick(); break;
  case 59: this->B59->animateClick(); break;
  case 60: this->B60->animateClick(); break;
  case 61: this->B61->animateClick(); break;
  case 62: this->B62->animateClick(); break;
  case 63: this->B63->animateClick(); break;
  case 82: this->B82->animateClick(); break;

  default:
    break;
  }

}

void TabMidi::receiveMidiNote2(int unBouton) // APC 2
{

  switch (unBouton)
  {
  // rangée 9 au dessus des sliders paint/color
  case 64: this->B64_2->animateClick(); break;
  case 65: this->B65_2->animateClick(); break;
  case 66: this->B66_2->animateClick(); break;
  case 67: this->B67_2->animateClick(); break;
  case 68: this->B68_2->animateClick(); break;
  case 69: this->B69_2->animateClick(); break;
  case 70: this->B70_2->animateClick(); break;
  case 71: this->B71_2->animateClick(); break;
  case 98: this->B98_2->animateClick(); break;

    // rangée 8 paint/rate
  case 0: this->B0_2->animateClick(); break;
  case 1: this->B1_2->animateClick(); break;
  case 2: this->B2_2->animateClick(); break;
  case 3: this->B3_2->animateClick(); break;
  case 4: this->B4_2->animateClick(); break;
  case 5: this->B5_2->animateClick(); break;
  case 6: this->B6_2->animateClick(); break;
  case 7: this->B7_2->animateClick(); break;
  case 89: this->B89_2->animateClick(); break;

    //rangée 7 mapping/solo off
  case 8: this->B8_2->animateClick(); break;
  case 9: this->B9_2->animateClick(); break;
  case 10: this->B10_2->animateClick(); break;
  case 11: this->B11_2->animateClick(); break;
  case 12: this->B12_2->animateClick(); break;
  case 13: this->B13_2->animateClick(); break;
  case 14: this->B14_2->animateClick(); break;
  case 15: this->B15_2->animateClick(); break;
  case 88: this->B88_2->animateClick(); break;

    // rangée 6 mapping/solo on
  case 16: this->B16_2->animateClick(); break;
  case 17: this->B17_2->animateClick(); break;
  case 18: this->B18_2->animateClick(); break;
  case 19: this->B19_2->animateClick(); break;
  case 20: this->B20_2->animateClick(); break;
  case 21: this->B21_2->animateClick(); break;
  case 22: this->B22_2->animateClick(); break;
  case 23: this->B23_2->animateClick(); break;
  case 87: this->B87_2->animateClick(); break;

    // rangée 5 mapping/visible off
  case 24: this->B24_2->animateClick(); break;
  case 25: this->B25_2->animateClick(); break;
  case 26: this->B26_2->animateClick(); break;
  case 27: this->B27_2->animateClick(); break;
  case 28: this->B28_2->animateClick(); break;
  case 29: this->B29_2->animateClick(); break;
  case 30: this->B30_2->animateClick(); break;
  case 31: this->B31_2->animateClick(); break;
  case 86: this->B86_2->animateClick(); break;

    // rangée 4 mapping/visible on
  case 32: this->B32_2->animateClick(); break;
  case 33: this->B33_2->animateClick(); break;
  case 34: this->B34_2->animateClick(); break;
  case 35: this->B35_2->animateClick(); break;
  case 36: this->B36_2->animateClick(); break;
  case 37: this->B37_2->animateClick(); break;
  case 38: this->B38_2->animateClick(); break;
  case 39: this->B39_2->animateClick(); break;
  case 85: this->B85_2->animateClick(); break;

    // rangée 3 paint/uri/ previous
  case 40: this->B40_2->animateClick(); break;
  case 41: this->B41_2->animateClick(); break;
  case 42: this->B42_2->animateClick(); break;
  case 43: this->B43_2->animateClick(); break;
  case 44: this->B44_2->animateClick(); break;
  case 45: this->B45_2->animateClick(); break;
  case 46: this->B46_2->animateClick(); break;
  case 47: this->B47_2->animateClick(); break;
  case 84: this->B84_2->animateClick(); break;

    // rangée 2 paint/uri next
  case 48: this->B48_2->animateClick(); break;
  case 49: this->B49_2->animateClick(); break;
  case 50: this->B50_2->animateClick(); break;
  case 51: this->B51_2->animateClick(); break;
  case 52: this->B52_2->animateClick(); break;
  case 53: this->B53_2->animateClick(); break;
  case 54: this->B54_2->animateClick(); break;
  case 55: this->B55_2->animateClick(); break;
  case 83: this->B83_2->animateClick(); break;

    // rangée 1 paint/uri uri
  case 56: this->B56_2->animateClick(); break;
  case 57: this->B57_2->animateClick(); break;
  case 58: this->B58_2->animateClick(); break;
  case 59: this->B59_2->animateClick(); break;
  case 60: this->B60_2->animateClick(); break;
  case 61: this->B61_2->animateClick(); break;
  case 62: this->B62_2->animateClick(); break;
  case 63: this->B63_2->animateClick(); break;
  case 82: this->B82_2->animateClick(); break;

  default:
    break;
  }

}

// APC 1
// mapping visible false
void TabMidi::sendOscAPCB64(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB65(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB66(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB67(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB68(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB69(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB70(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB71(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB98(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
// mapping visible true
void TabMidi::sendOscAPCB0(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB1(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB3(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB4(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB5(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB6(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB7(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB89(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
// mapping solo false
void TabMidi::sendOscAPCB8(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB9(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB10(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB11(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB12(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB13(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB14(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB15(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB88(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
// mapping solo true
void TabMidi::sendOscAPCB16(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB17(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB18(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB19(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB20(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB21(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB22(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB23(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB87(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
// rate -100%
void TabMidi::sendOscAPCB24(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID1->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB25(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID2->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB26(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID3->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB27(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID4->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB28(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID5->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB29(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID6->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB30(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID7->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB31(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID8->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB86(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID9->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
// rate 50%
void TabMidi::sendOscAPCB32(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID1->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB33(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID2->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB34(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID3->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB35(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID4->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB36(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID5->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB37(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID6->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB38(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID7->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB39(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID8->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB85(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID9->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
// rate 100%
void TabMidi::sendOscAPCB40(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID1->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB41(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID2->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB42(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID3->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB43(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID4->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB44(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID5->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB45(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID6->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB46(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID7->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB47(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID8->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB84(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID9->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
// rate 200%
void TabMidi::sendOscAPCB48(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID1->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB49(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID2->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB50(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID3->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB51(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID4->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB52(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID5->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB53(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID6->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB54(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID7->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB55(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID8->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB83(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID9->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
// rewind
void TabMidi::sendOscAPCB56(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID1->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB57(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID2->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB58(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID3->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB59(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID4->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB60(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID5->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB61(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID6->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB62(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID7->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB63(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID8->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB82(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID9->value(); oscSendB->ExecuteSend(); }

// APC 2 // Reprendre les dernières lignes pour en faire des masters regexp et play/pause
// mapping visible false
void TabMidi::sendOscAPCB64_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID10->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB65_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID11->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB66_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID12->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB67_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID13->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB68_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID14->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB69_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID15->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB70_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID16->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB71_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID17->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB98_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID18->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
// mapping visible true
void TabMidi::sendOscAPCB0_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID10->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB1_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID11->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB2_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID12->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB3_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID13->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB4_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID14->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB5_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID15->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB6_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID16->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB7_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID17->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB89_2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID18->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
// mapping solo false
void TabMidi::sendOscAPCB8_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID10->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB9_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID11->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB10_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID12->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB11_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID13->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB12_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID14->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB13_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID15->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB14_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID16->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB15_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID17->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB88_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID18->value(); oscSendB->m_m_issolo = false; oscSendB->ExecuteSend(); }
// mapping solo true
void TabMidi::sendOscAPCB16_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID10->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB17_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID11->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB18_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID12->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB19_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID13->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB20_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID14->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB21_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID15->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB22_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID16->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB23_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID17->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB87_2(){ oscSendB->m_champ = M_SOLO; oscSendB->m_m_ID1 = mID18->value(); oscSendB->m_m_issolo = true; oscSendB->ExecuteSend(); }
// rate -100%
void TabMidi::sendOscAPCB24_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID10->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB25_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID11->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB26_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID12->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB27_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID13->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB28_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID14->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB29_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID15->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB30_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID16->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB31_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID17->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB86_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID18->value(); oscSendB->m_p_rate = -100; oscSendB->ExecuteSend(); }
// rate 50%
void TabMidi::sendOscAPCB32_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID10->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB33_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID11->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB34_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID12->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB35_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID13->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB36_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID14->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB37_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID15->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB38_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID16->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB39_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID17->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB85_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID18->value(); oscSendB->m_p_rate = 50; oscSendB->ExecuteSend(); }
// rate 100%
void TabMidi::sendOscAPCB40_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID10->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB41_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID11->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB42_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID12->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB43_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID13->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB44_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID14->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB45_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID15->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB46_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID16->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB47_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID17->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB84_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID18->value(); oscSendB->m_p_rate = 100; oscSendB->ExecuteSend(); }
// rate 200%
void TabMidi::sendOscAPCB48_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID10->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB49_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID11->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB50_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID12->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB51_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID13->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB52_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID14->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB53_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID15->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB54_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID16->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB55_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID17->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB83_2(){ oscSendB->m_champ = P_RATE; oscSendB->m_p_ID1 = pID18->value(); oscSendB->m_p_rate = 200; oscSendB->ExecuteSend(); }

void TabMidi::sendOscAPCB56_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID10->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB57_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID11->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB58_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID12->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB59_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID13->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB60_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID14->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB61_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID15->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB62_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID16->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB63_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID17->value(); oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB82_2(){ oscSendB->m_champ = P_REWIND; oscSendB->m_p_ID1 = pID18->value(); oscSendB->ExecuteSend(); }
