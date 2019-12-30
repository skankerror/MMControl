#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "mmstate.h"
#include "mymidiin.h"
#include "tabmidi.h"
#include "tabseq.h"
#include "tabmmstate.h"
#include "oscsend.h"
#include "osccuelist.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    void createCentralWidget();
    void createToolBar();

    OscCueList *oscCueList;
    MMState *state;

signals:

public slots:
    void showWidgets(int index);
    void sendFromToolBar();
    void setP_UriLabel();
    void setP_ColorLabel();
    void addToCue();

private:
    TabMidi *tabmidi;
    TabSeq *tabseq;
    TabMMState *tabmmstate;
    QTabWidget *tabwidget;

    QToolBar *myToolBar;
    QLabel *champLabel;
    QComboBox *champComboBox;
    QLabel *p_uriLabel;
    QPushButton *p_uriPushButton;
    QLineEdit *p_nameLineEdit;
    QLabel *p_colorLabel;
    QPushButton *p_colorPushButton;
    QLabel *p_ID1Label;
    QSpinBox *p_ID1SpinBox;
    QLabel *p_ID2Label;
    QSpinBox *p_ID2SpinBox;
    QLabel *p_rateLabel;
    QSpinBox *p_rateSpinBox;
    QLabel *p_opacityLabel;
    QSpinBox *p_opacitySpinBox;
    QLabel *p_volumeLabel;
    QSpinBox *p_volumeSpinBox;
    QLineEdit *m_nameLineEdit;
    QLabel *m_IDLabel;
    QSpinBox *m_IDSpinBox;
    QLabel *m_opacityLabel;
    QSpinBox *m_opacitySpinBox;
    QCheckBox *m_visibleCheckBox;
    QCheckBox *m_soloCheckBox;
    QCheckBox *m_lockCheckBox;
    QLabel *m_depthLabel;
    QSpinBox *m_depthSpinBox;
    QLabel *timeLabel;
    QSpinBox *timeSpinBox;
    QCheckBox *fadeCheckBox;
    QPushButton *sendPushButton;
    QPushButton *addToCuePushButton;



};

#endif // MAINWINDOW_H
