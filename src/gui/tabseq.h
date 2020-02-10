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
#include "osccuelistdelegate.h"
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
  void updateProgressTime(int value);
  void progressTimeFinished();

public slots:
  void executeGo();
//  void executeCue(OscCue *osccue);
  void executeSend(OscSend *oscsend);
  void movePrevious();
  void moveNext();
  void remove();
  void addCue();
  void saveAs();
  void loadFile();
  void receiveMidiNote2(int note);
  void timeProgressFinished();
  void timeProgressSteped();
  void selectNextRow();

  void hideShowColumns();

private:
  OscCueList *m_oscCueList;
  MyMidiIn *m_midiIn1;
  MyMidiIn *m_midiIn2;
  MyMidiOut *m_midiOut1;
  MyMidiOut *m_midiOut2;
  OscCuelistDelegate *m_delegate;
  OscCueListProxy *proxyModel;

  QHBoxLayout *layoutMain;
    QHBoxLayout *layout1;
      QVBoxLayout *boutonLayout;
        QPushButton *boutonPrev;
        QPushButton *boutonNext;
        QPushButton *boutonRemove;
        QPushButton *boutonAddCue;
        QPushButton *boutonGo;
        QPushButton *boutonSaveAs;
        QPushButton *boutonLoad;

//  OscCue *tempCue;
  OscSend *tempSend;

public:
  QTreeView *treeView;
  int counter = 0;
  double totalTime = 0;

};

#endif // TABSEQ_H
