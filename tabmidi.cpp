#include "tabmidi.h"

TabMidi::TabMidi(QWidget *parent) : QWidget(parent)
{
  MyMidiIn *midiin = new MyMidiIn;
  oscSendS = new OscSend(P_OPACITY, 1, 0, 0);
  oscSendB = new OscSend(M_VISIBLE, 1, true);
  layoutTotal = new QHBoxLayout;
  headerLayout = new QVBoxLayout;
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
  headerLayout->addWidget(labelb9); headerLayout->addWidget(labelb8);
  headerLayout->addWidget(labelb7); headerLayout->addWidget(labelb6);
  headerLayout->addWidget(labelb5); headerLayout->addWidget(labelb4);
  headerLayout->addWidget(labelb3); headerLayout->addWidget(labelb2);
  headerLayout->addWidget(labelb1); headerLayout->addWidget(labelS);
  headerLayout->addWidget(labelPid); headerLayout->addWidget(labelMid);
  bLayout1 = new QVBoxLayout;
  B64 = new QPushButton; B0 = new QPushButton; B8 = new QPushButton;
  B16 = new QPushButton; B24 = new QPushButton; B32 = new QPushButton;
  B40 = new QPushButton; B48 = new QPushButton; B56 = new QPushButton;
  S1 = new QSlider(Qt::Vertical);
  pID1 = new QSpinBox; pID1->setValue(1); mID1 = new QSpinBox; mID1->setValue(1);
  bLayout1->addWidget(B56); bLayout1->addWidget(B48); bLayout1->addWidget(B40);
  bLayout1->addWidget(B32); bLayout1->addWidget(B24); bLayout1->addWidget(B16);
  bLayout1->addWidget(B8); bLayout1->addWidget(B0); bLayout1->addWidget(B64);
  bLayout1->addWidget(S1); bLayout1->addWidget(pID1);bLayout1->addWidget(mID1);

  bLayout2 = new QVBoxLayout;
  B65 = new QPushButton; B1 = new QPushButton; B9 = new QPushButton;
  B17 = new QPushButton; B25 = new QPushButton; B33 = new QPushButton;
  B41 = new QPushButton; B49 = new QPushButton; B57 = new QPushButton;
  S2 = new QSlider(Qt::Vertical);
  pID2 = new QSpinBox; pID2->setValue(2); mID2 = new QSpinBox; mID2->setValue(2);
  bLayout2->addWidget(B57); bLayout2->addWidget(B49); bLayout2->addWidget(B41);
  bLayout2->addWidget(B33); bLayout2->addWidget(B25); bLayout2->addWidget(B17);
  bLayout2->addWidget(B9); bLayout2->addWidget(B1); bLayout2->addWidget(B65);
  bLayout2->addWidget(S2); bLayout2->addWidget(pID2);bLayout2->addWidget(mID2);

  bLayout3 = new QVBoxLayout;
  B66 = new QPushButton; B2 = new QPushButton; B10 = new QPushButton;
  B18 = new QPushButton; B26 = new QPushButton; B34 = new QPushButton;
  B42 = new QPushButton; B50 = new QPushButton; B58 = new QPushButton;
  S3 = new QSlider(Qt::Vertical);
  pID3 = new QSpinBox; pID3->setValue(3); mID3 = new QSpinBox; mID3->setValue(3);
  bLayout3->addWidget(B58); bLayout3->addWidget(B50); bLayout3->addWidget(B42);
  bLayout3->addWidget(B34); bLayout3->addWidget(B26); bLayout3->addWidget(B18);
  bLayout3->addWidget(B10); bLayout3->addWidget(B2); bLayout3->addWidget(B66);
  bLayout3->addWidget(S3); bLayout3->addWidget(pID3);bLayout3->addWidget(mID3);

  bLayout4 = new QVBoxLayout;
  B67 = new QPushButton; B3 = new QPushButton; B11 = new QPushButton;
  B19 = new QPushButton; B27 = new QPushButton; B35 = new QPushButton;
  B43 = new QPushButton; B51 = new QPushButton; B59 = new QPushButton;
  S4 = new QSlider(Qt::Vertical);
  pID4 = new QSpinBox; pID4->setValue(4); mID4 = new QSpinBox; mID4->setValue(4);
  bLayout4->addWidget(B59); bLayout4->addWidget(B51); bLayout4->addWidget(B43);
  bLayout4->addWidget(B35); bLayout4->addWidget(B27); bLayout4->addWidget(B19);
  bLayout4->addWidget(B11); bLayout4->addWidget(B3); bLayout4->addWidget(B67);
  bLayout4->addWidget(S4); bLayout4->addWidget(pID4);bLayout4->addWidget(mID4);

  bLayout5 = new QVBoxLayout;
  B68 = new QPushButton; B4 = new QPushButton; B12 = new QPushButton;
  B20 = new QPushButton; B28 = new QPushButton; B36 = new QPushButton;
  B44 = new QPushButton; B52 = new QPushButton; B60 = new QPushButton;
  S5 = new QSlider(Qt::Vertical);
  pID5 = new QSpinBox; pID5->setValue(5); mID5 = new QSpinBox; mID5->setValue(5);
  bLayout5->addWidget(B60); bLayout5->addWidget(B52); bLayout5->addWidget(B44);
  bLayout5->addWidget(B36); bLayout5->addWidget(B28); bLayout5->addWidget(B20);
  bLayout5->addWidget(B12); bLayout5->addWidget(B4); bLayout5->addWidget(B68);
  bLayout5->addWidget(S5); bLayout5->addWidget(pID5);bLayout5->addWidget(mID5);

  bLayout6 = new QVBoxLayout;
  B69 = new QPushButton; B5 = new QPushButton; B13 = new QPushButton;
  B21 = new QPushButton; B29 = new QPushButton; B37 = new QPushButton;
  B45 = new QPushButton; B53 = new QPushButton; B61 = new QPushButton;
  S6 = new QSlider(Qt::Vertical);
  pID6 = new QSpinBox; pID6->setValue(6); mID6 = new QSpinBox; mID6->setValue(6);
  bLayout6->addWidget(B61); bLayout6->addWidget(B53); bLayout6->addWidget(B45);
  bLayout6->addWidget(B37); bLayout6->addWidget(B29); bLayout6->addWidget(B21);
  bLayout6->addWidget(B13); bLayout6->addWidget(B5); bLayout6->addWidget(B69);
  bLayout6->addWidget(S6); bLayout6->addWidget(pID6);bLayout6->addWidget(mID6);

  bLayout7 = new QVBoxLayout;
  B70 = new QPushButton; B6 = new QPushButton; B14 = new QPushButton;
  B22 = new QPushButton; B30 = new QPushButton; B38 = new QPushButton;
  B46 = new QPushButton; B54 = new QPushButton; B62 = new QPushButton;
  S7 = new QSlider(Qt::Vertical);
  pID7 = new QSpinBox; pID7->setValue(7); mID7 = new QSpinBox; mID7->setValue(7);
  bLayout7->addWidget(B62); bLayout7->addWidget(B54); bLayout7->addWidget(B46);
  bLayout7->addWidget(B38); bLayout7->addWidget(B30); bLayout7->addWidget(B22);
  bLayout7->addWidget(B14); bLayout7->addWidget(B6); bLayout7->addWidget(B70);
  bLayout7->addWidget(S7); bLayout7->addWidget(pID7);bLayout7->addWidget(mID7);

  bLayout8 = new QVBoxLayout;
  B71 = new QPushButton; B7 = new QPushButton; B15 = new QPushButton;
  B23 = new QPushButton; B31 = new QPushButton; B39 = new QPushButton;
  B47 = new QPushButton; B55 = new QPushButton; B63 = new QPushButton;
  S8 = new QSlider(Qt::Vertical);
  pID8 = new QSpinBox; pID8->setValue(8); mID8 = new QSpinBox; mID8->setValue(8);
  bLayout8->addWidget(B63); bLayout8->addWidget(B55); bLayout8->addWidget(B47);
  bLayout8->addWidget(B39); bLayout8->addWidget(B31); bLayout8->addWidget(B23);
  bLayout8->addWidget(B18); bLayout8->addWidget(B7); bLayout8->addWidget(B71);
  bLayout8->addWidget(S8); bLayout8->addWidget(pID8);bLayout8->addWidget(mID8);

  bLayout9 = new QVBoxLayout;
  B98 = new QPushButton; B89 = new QPushButton; B88 = new QPushButton;
  B87 = new QPushButton; B86 = new QPushButton; B85 = new QPushButton;
  B84 = new QPushButton; B83 = new QPushButton; B82 = new QPushButton;
  S9 = new QSlider(Qt::Vertical);
  pID9 = new QSpinBox; pID9->setValue(9); mID9 = new QSpinBox; mID9->setValue(9);
  bLayout9->addWidget(B82); bLayout9->addWidget(B83); bLayout9->addWidget(B84);
  bLayout9->addWidget(B85); bLayout9->addWidget(B86); bLayout9->addWidget(B87);
  bLayout9->addWidget(B88); bLayout9->addWidget(B89); bLayout9->addWidget(B98);
  bLayout9->addWidget(S9); bLayout9->addWidget(pID9);bLayout9->addWidget(mID9);

  layoutTotal->addLayout(headerLayout);
  layoutTotal->addLayout(bLayout1);
  layoutTotal->addLayout(bLayout2);
  layoutTotal->addLayout(bLayout3);
  layoutTotal->addLayout(bLayout4);
  layoutTotal->addLayout(bLayout5);
  layoutTotal->addLayout(bLayout6);
  layoutTotal->addLayout(bLayout7);
  layoutTotal->addLayout(bLayout8);
  layoutTotal->addLayout(bLayout9);

  this->setLayout(layoutTotal);

  connect(midiin, SIGNAL(sigMidiCtrlChanged(int, float)), this, SLOT(receiveMidiCtrl(int,float)));
  connect(midiin, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote(int)));
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


