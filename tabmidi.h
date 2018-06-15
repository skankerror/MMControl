#ifndef TABMIDI_H
#define TABMIDI_H

#include <QWidget>
#include <QSlider>
#include <QBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include "mymidiin.h"
#include "oscsend.h"

class TabMidi : public QWidget
{
    Q_OBJECT
public:
    explicit TabMidi(QWidget *parent = nullptr);

signals:

public slots:
    // voir le cpp à refaire.
    // Pour quand on reçoit du midiin.
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


private:
    OscSend *oscSendS;
    OscSend *oscSendB;
    QVBoxLayout *layoutTotal;
    QHBoxLayout *sLayout;
        QSlider *S1; QSlider *S2; QSlider *S3; QSlider *S4; QSlider *S5; QSlider *S6; QSlider *S7; QSlider *S8; QSlider *S9;
    QHBoxLayout *pIDLayout;
        QSpinBox *pID1; QSpinBox *pID2; QSpinBox *pID3; QSpinBox *pID4; QSpinBox *pID5; QSpinBox *pID6; QSpinBox *pID7; QSpinBox *pID8; QSpinBox *pID9;
    QHBoxLayout *mIDLayout;
        QSpinBox *mID1; QSpinBox *mID2; QSpinBox *mID3; QSpinBox *mID4; QSpinBox *mID5; QSpinBox *mID6; QSpinBox *mID7; QSpinBox *mID8; QSpinBox *mID9;
    QHBoxLayout *bLayoutTotal;
        QVBoxLayout *bLayout1;
            QPushButton *B64; QPushButton *B0; QPushButton *B8; QPushButton *B16; QPushButton *B24; QPushButton *B32; QPushButton *B40; QPushButton *B48; QPushButton *B56;
        QVBoxLayout *bLayout2;
            QPushButton *B65; QPushButton *B1; QPushButton *B9; QPushButton *B17; QPushButton *B25; QPushButton *B33; QPushButton *B41; QPushButton *B49; QPushButton *B57;
        QVBoxLayout *bLayout3;
            QPushButton *B66;
            QPushButton *B2; QPushButton *B10; QPushButton *B18; QPushButton *B26; QPushButton *B34; QPushButton *B42; QPushButton *B50; QPushButton *B58;
        QVBoxLayout *bLayout4;
            QPushButton *B67; QPushButton *B3; QPushButton *B11; QPushButton *B19; QPushButton *B27; QPushButton *B35; QPushButton *B43; QPushButton *B51; QPushButton *B59;
        QVBoxLayout *bLayout5;
            QPushButton *B68; QPushButton *B4; QPushButton *B12; QPushButton *B20; QPushButton *B28; QPushButton *B36; QPushButton *B44; QPushButton *B52; QPushButton *B60;
        QVBoxLayout *bLayout6;
            QPushButton *B69; QPushButton *B5; QPushButton *B13; QPushButton *B21; QPushButton *B29; QPushButton *B37; QPushButton *B45; QPushButton *B53; QPushButton *B61;
        QVBoxLayout *bLayout7;
            QPushButton *B70; QPushButton *B6; QPushButton *B14; QPushButton *B22; QPushButton *B30; QPushButton *B38; QPushButton *B46; QPushButton *B54; QPushButton *B62;
        QVBoxLayout *bLayout8;
            QPushButton *B71; QPushButton *B7; QPushButton *B15; QPushButton *B23; QPushButton *B31; QPushButton *B39; QPushButton *B47; QPushButton *B55; QPushButton *B63;
        QVBoxLayout *bLayout9;
            QPushButton *B98; QPushButton *B89; QPushButton *B88; QPushButton *B87; QPushButton *B86; QPushButton *B85; QPushButton *B84; QPushButton *B83; QPushButton *B82;
};

#endif // TABMIDI_H
