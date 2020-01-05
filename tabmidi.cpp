#include "tabmidi.h"

TabMidi::TabMidi(MyMidiIn *midiIn, QWidget *parent) :
  QWidget(parent),
    m_midiIn(midiIn)
{
  //MyMidiIn *midiin = new MyMidiIn;
  oscSendS = new OscSend(P_OPACITY, 1, 0, 0);
  oscSendB = new OscSend(M_VISIBLE, 1, true);
  layoutTotal = new QGridLayout;
//  headerLayout = new QVBoxLayout;
  labelb9 = new QLabel("noop");
  labelb8 = new QLabel("noop");
  labelb7 = new QLabel("noop");
  labelb6 = new QLabel("noop");
  labelb5 = new QLabel("noop");
  labelb4 = new QLabel("noop");
  labelb3 = new QLabel("noop");
  labelb2 = new QLabel("Mesh Not Visible");
  labelb1 = new QLabel("Mesh Visible");
  labelS = new QLabel("paint_opacity");
  labelPid = new QLabel("paint id");
  labelMid = new QLabel("mesh id");
  layoutTotal->addWidget(labelb9, 0, 0); layoutTotal->addWidget(labelb8, 1, 0);
  layoutTotal->addWidget(labelb7, 2, 0); layoutTotal->addWidget(labelb6, 3, 0);
  layoutTotal->addWidget(labelb5, 4, 0); layoutTotal->addWidget(labelb4, 5, 0);
  layoutTotal->addWidget(labelb3, 6, 0); layoutTotal->addWidget(labelb2, 7, 0);
  layoutTotal->addWidget(labelb1, 8, 0); layoutTotal->addWidget(labelS, 9, 0);
  layoutTotal->addWidget(labelPid, 10, 0); layoutTotal->addWidget(labelMid, 11, 0);

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

  // align sliders
  layoutTotal->setAlignment(S1, Qt::AlignHCenter);
  layoutTotal->setAlignment(S2, Qt::AlignHCenter);
  layoutTotal->setAlignment(S3, Qt::AlignHCenter);
  layoutTotal->setAlignment(S4, Qt::AlignHCenter);
  layoutTotal->setAlignment(S5, Qt::AlignHCenter);
  layoutTotal->setAlignment(S6, Qt::AlignHCenter);
  layoutTotal->setAlignment(S7, Qt::AlignHCenter);
  layoutTotal->setAlignment(S8, Qt::AlignHCenter);
  layoutTotal->setAlignment(S9, Qt::AlignHCenter);

  this->setLayout(layoutTotal);

  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::gray);
  setAutoFillBackground(true);
  setPalette(pal);

  connect(m_midiIn, SIGNAL(sigMidiCtrlChanged(int, float)), this, SLOT(receiveMidiCtrl(int,float)));
  connect(m_midiIn, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote(int)));
  //connections des sliders
  {connect(this->S1, SIGNAL(valueChanged(int)), this, SLOT(sendOscS1(int)));
    connect(this->S2, SIGNAL(valueChanged(int)), this, SLOT(sendOscS2(int)));
    connect(this->S3, SIGNAL(valueChanged(int)), this, SLOT(sendOscS3(int)));
    connect(this->S4, SIGNAL(valueChanged(int)), this, SLOT(sendOscS4(int)));
    connect(this->S5, SIGNAL(valueChanged(int)), this, SLOT(sendOscS5(int)));
    connect(this->S6, SIGNAL(valueChanged(int)), this, SLOT(sendOscS6(int)));
    connect(this->S7, SIGNAL(valueChanged(int)), this, SLOT(sendOscS7(int)));
    connect(this->S8, SIGNAL(valueChanged(int)), this, SLOT(sendOscS8(int)));
    connect(this->S9, SIGNAL(valueChanged(int)), this, SLOT(sendOscS9(int)));}

  // connections de tous les boutons !
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

}


void TabMidi::receiveMidiCtrl(int unID, float uneOpacite)
{

  switch(unID)
  {
  case 1: this->S1->setValue((int)(uneOpacite*100)); break;
  case 2: this->S2->setValue((int)(uneOpacite*100)); break;
  case 3: this->S3->setValue((int)(uneOpacite*100)); break;
  case 4: this->S4->setValue((int)(uneOpacite*100)); break;
  case 5: this->S5->setValue((int)(uneOpacite*100)); break;
  case 6: this->S6->setValue((int)(uneOpacite*100)); break;
  case 7: this->S7->setValue((int)(uneOpacite*100)); break;
  case 8: this->S8->setValue((int)(uneOpacite*100)); break;
  case 9: this->S9->setValue((int)(uneOpacite*100)); break;

  default : break;
  }
}

void TabMidi::sendOscS1(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID1->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS2(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID2->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS3(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID3->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS4(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID4->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS5(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID5->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS6(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID6->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS7(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID7->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS8(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID8->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}
void TabMidi::sendOscS9(int uneOpacite)
{
  oscSendS->m_p_ID1 = pID9->value();
  oscSendS->m_p_opacity = uneOpacite;
  oscSendS->ExecuteSend();
}

void TabMidi::receiveMidiNote(int unBouton)
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

void TabMidi::sendOscAPCB64(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB65(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB66(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB67(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB68(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB69(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB70(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB71(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }
void TabMidi::sendOscAPCB98(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_isvisible = false; oscSendB->ExecuteSend(); }

void TabMidi::sendOscAPCB0(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID1->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB1(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID2->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB2(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID3->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB3(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID4->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB4(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID5->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB5(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID6->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB6(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID7->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB7(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID8->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}
void TabMidi::sendOscAPCB89(){ oscSendB->m_champ = M_VISIBLE; oscSendB->m_m_ID1 = mID9->value(); oscSendB->m_m_isvisible = true; oscSendB->ExecuteSend();}

void TabMidi::sendOscAPCB8(){  }
void TabMidi::sendOscAPCB9(){  }
void TabMidi::sendOscAPCB10(){  }
void TabMidi::sendOscAPCB11(){  }
void TabMidi::sendOscAPCB12(){  }
void TabMidi::sendOscAPCB13(){  }
void TabMidi::sendOscAPCB14(){  }
void TabMidi::sendOscAPCB15(){  }
void TabMidi::sendOscAPCB88(){  }

void TabMidi::sendOscAPCB16(){  }
void TabMidi::sendOscAPCB17(){  }
void TabMidi::sendOscAPCB18(){  }
void TabMidi::sendOscAPCB19(){  }
void TabMidi::sendOscAPCB20(){  }
void TabMidi::sendOscAPCB21(){  }
void TabMidi::sendOscAPCB22(){  }
void TabMidi::sendOscAPCB23(){  }
void TabMidi::sendOscAPCB87(){  }

void TabMidi::sendOscAPCB24(){  }
void TabMidi::sendOscAPCB25(){  }
void TabMidi::sendOscAPCB26(){  }
void TabMidi::sendOscAPCB27(){  }
void TabMidi::sendOscAPCB28(){  }
void TabMidi::sendOscAPCB29(){  }
void TabMidi::sendOscAPCB30(){  }
void TabMidi::sendOscAPCB31(){  }
void TabMidi::sendOscAPCB86(){  }

void TabMidi::sendOscAPCB32(){  }
void TabMidi::sendOscAPCB33(){  }
void TabMidi::sendOscAPCB34(){  }
void TabMidi::sendOscAPCB35(){  }
void TabMidi::sendOscAPCB36(){  }
void TabMidi::sendOscAPCB37(){  }
void TabMidi::sendOscAPCB38(){  }
void TabMidi::sendOscAPCB39(){  }
void TabMidi::sendOscAPCB85(){  }

void TabMidi::sendOscAPCB40(){ /*Paint uri prev 1 */  }
void TabMidi::sendOscAPCB41(){ /*Paint uri prev 2 */  }
void TabMidi::sendOscAPCB42(){ /*Paint uri prev 3 */  }
void TabMidi::sendOscAPCB43(){ /*Paint uri prev 4 */  }
void TabMidi::sendOscAPCB44(){ /*Paint uri prev 5 */  }
void TabMidi::sendOscAPCB45(){ /*Paint uri prev 6 */  }
void TabMidi::sendOscAPCB46(){ /*Paint uri prev 7 */  }
void TabMidi::sendOscAPCB47(){ /*Paint uri prev 8 */  }
void TabMidi::sendOscAPCB84(){ /*Paint uri prev 9 */  }

void TabMidi::sendOscAPCB48(){ /*Paint uri next 1 */  }
void TabMidi::sendOscAPCB49(){ /*Paint uri next 2 */  }
void TabMidi::sendOscAPCB50(){ /*Paint uri next 3 */  }
void TabMidi::sendOscAPCB51(){ /*Paint uri next 4 */  }
void TabMidi::sendOscAPCB52(){ /*Paint uri next 5 */  }
void TabMidi::sendOscAPCB53(){ /*Paint uri next 6 */  }
void TabMidi::sendOscAPCB54(){ /*Paint uri next 7 */  }
void TabMidi::sendOscAPCB55(){ /*Paint uri next 8 */  }
void TabMidi::sendOscAPCB83(){ /*Paint uri next 9 */  }

void TabMidi::sendOscAPCB56(){ /*Paint uri 1 */  }
void TabMidi::sendOscAPCB57(){ /*Paint uri 2 */  }
void TabMidi::sendOscAPCB58(){ /*Paint uri 3 */  }
void TabMidi::sendOscAPCB59(){ /*Paint uri 4 */  }
void TabMidi::sendOscAPCB60(){ /*Paint uri 5 */  }
void TabMidi::sendOscAPCB61(){ /*Paint uri 6 */  }
void TabMidi::sendOscAPCB62(){ /*Paint uri 7 */  }
void TabMidi::sendOscAPCB63(){ /*Paint uri 8 */  }
void TabMidi::sendOscAPCB82(){ /*Paint uri 9 */  }


