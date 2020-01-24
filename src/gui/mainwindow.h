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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "mmstate.h"
#include "mymidiin.h"
#include "mymidiout.h"
#include "tableview.h"
#include "tabmidi.h"
#include "tabseq.h"
#include "tabmmstate.h"
#include "oscsend.h"
#include "osccuelist.h"
#include "MMC.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow();

  void createCentralWidget();
  void createToolBar();

protected:
  void closeEvent(QCloseEvent *event) override;

signals:

public slots:
  void showWidgets(int index);
  void sendFromToolBar();
  void setP_UriLine();
  void setP_ColorLine();
  void addToCue();

private:
  OscCueList *oscCueList;
  MMState *state;
  MyMidiIn *midiIn1;
  MyMidiIn *midiIn2;
  MyMidiOut *midiOut1;
  MyMidiOut *midiOut2;
//  TableView *tableView;
  QTreeView *treeView;

  QIcon icon;

  QTabWidget *tabwidget;
    TabMidi *tabmidi;
    TabSeq *tabseq;
    TabMMState *tabmmstate;

  QToolBar *myToolBar;
    QLabel *champLabel;
    QComboBox *champComboBox;
    QLineEdit *p_nameLineEdit;
    QLineEdit *p_nameLineEdit2;
//    QLabel *p_uriLabel;
    QLineEdit *p_uriLine;
    QPushButton *p_uriPushButton;
//    QLabel *p_colorLabel;
    QLineEdit *p_colorLine;
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
    QLineEdit *m_nameLineEdit2;
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
    QDoubleSpinBox *timeSpinBox;
    QCheckBox *fadeCheckBox;
    QLabel *waitTimeLabel;
    QDoubleSpinBox *waitTimeSpinBox;

    QPushButton *sendPushButton;
    QPushButton *addToCuePushButton;

};

#endif // MAINWINDOW_H
