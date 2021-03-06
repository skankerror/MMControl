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

#ifndef TABSEQ_H
#define TABSEQ_H

#include <QtWidgets>
#include "osccuelist.h"
#include "mymidi.h"
#include "MMC.h"

class TabSeq : public QWidget
{
  Q_OBJECT
public:
  TabSeq(OscCueList *oscCueList,
         QTreeView *atreeView,
         MyMidiIn *midiIn1,
         MyMidiIn *midiIn2,
         MyMidiOut *midiOut1,
         MyMidiOut *midiOut2,
         QWidget *parent = nullptr);

signals:
  void updateProgressTimeCue(int value);
  void progressTimeFinishedCue();
  void updateProgressTimeSend(int value);
  void progressTimeFinishedSend();
  void updateProgressTimeWaitSend(int value);
  void progressTimeWaitFinishedSend();
  void sendStringToOutputLabel(QString);
  void disconnectButtonsToolBar();
  void reconnectButtonsToolBar();
  void askGoToCue(int); // Y connecter un bouton pour asker à mainwindow

public slots:
  void executeGo();
  void executeSend(OscSend *oscsend);
  void movePrevious();
  void moveNext();
  void remove();
  void addCue();
  void saveAs();
  void loadFile();
  void receiveMidiNote2(int note);
  void timeProgressFinishedCue();
  void timeProgressStepedCue();
  void timeProgressFinishedSend();
  void timeProgressStepedSend();
  void timeWaitProgressFinishedSend();
  void timeWaitProgressStepedSend();
  void selectRow();
  void receiveStringFromSend(QString tempString);
  void sendWaitToOutputLabel();
  void resetOutputLabel();
  void disconnectButtons();
  void reconnectButtons();
  void stopCue();
  void GoToCue();

  void hideShowColumns();

private:
  OscCueList *m_oscCueList;
  MyMidiIn *m_midiIn1;
  MyMidiIn *m_midiIn2;
  MyMidiOut *m_midiOut1;
  MyMidiOut *m_midiOut2;
  OscCuelistDelegate *m_delegate;

  QHBoxLayout *layoutMain;
    QHBoxLayout *layout1;
      QVBoxLayout *boutonLayout;
        QPushButton *boutonPrev;
        QPushButton *boutonNext;
        QPushButton *boutonRemove;
        QPushButton *boutonStop;
        QPushButton *boutonAddCue;
        QPushButton *boutonGo;
        QPushButton *boutonSaveAs;
        QPushButton *boutonLoad;
        QPushButton *boutonGoToCue;

  // pour executeGo
  OscSend *tempSend = nullptr;
  int counterCue = 0;
  double totalTime = 0;
  int counterSend = 0;
  int counterSendWait = 0;
  double totalTimeSend = 0;
  double fadeTimeSend = 0;
  double waitTimeSend = 0;
  QTimer *timerWait; // pour le wait
  QTimer *timerTotal; // pour passer au row suivant

public:
  QTreeView *treeView;

};

#endif // TABSEQ_H
