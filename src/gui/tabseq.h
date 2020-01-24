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

#include <QWidget>
#include <QtWidgets>
#include <QBoxLayout>
#include <QTimer>
#include <unistd.h>
#include "osccuelist.h"
#include "tableview.h"
#include "mymidiin.h"
#include "mymidiout.h"
#include "osccuelistdelegate.h"

class TabSeq : public QWidget
{
  Q_OBJECT
public:
  TabSeq(OscCueList *oscCueList,
         QTreeView *aTreeView,
         MyMidiIn *midiIn1,
         MyMidiIn *midiIn2,
         MyMidiOut *midiOut1,
         MyMidiOut *midiOut2,
         QWidget *parent = nullptr);

signals:



public slots:
  void executeGo();
  void movePrevious();
  void moveNext();
  void removeCue();
  void saveAs();
  void loadFile();

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
        QPushButton *boutonGo;
        QPushButton *boutonSaveAs;
        QPushButton *boutonLoad;

public:
  QTreeView *treeView;

};

#endif // TABSEQ_H
