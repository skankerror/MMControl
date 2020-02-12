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

#include "tabseq.h"

TabSeq::TabSeq(OscCueList *oscCueList,
               QTreeView *atreeView,
               MyMidiIn *midiIn1,
               MyMidiIn *midiIn2,
               MyMidiOut *midiOut1,
               MyMidiOut *midiOut2,
               QWidget *parent
               ):
  QWidget(parent),
  m_oscCueList(oscCueList),
  m_midiIn1(midiIn1),
  m_midiIn2(midiIn2),
  m_midiOut1(midiOut1),
  m_midiOut2(midiOut2),
  treeView(atreeView)
{
  // On met une cue pour démarrer
//  m_oscCueList->addCue();

  layoutMain = new QHBoxLayout();
  layout1 = new QHBoxLayout();
  boutonLayout = new QVBoxLayout();

  boutonPrev = new QPushButton(this);
  QIcon upIcon = QIcon(":/graphics/UpArrow");
  boutonPrev->setIcon(upIcon);
  boutonPrev->setFixedSize(80, 40);
  boutonPrev->setIconSize(QSize(70, 30));

  boutonNext = new QPushButton(this);
  QIcon downIcon = QIcon(":/graphics/DownArrow");
  boutonNext->setIcon(downIcon);
  boutonNext->setFixedSize(80, 40);
  boutonNext->setIconSize(QSize(70, 30));

  boutonRemove = new QPushButton(this);
  QIcon binIcon = QIcon(":/graphics/Bin");
  boutonRemove->setIcon(binIcon);
  boutonRemove->setFixedSize(80, 40);
  boutonRemove->setIconSize(QSize(70, 30));

  boutonAddCue = new QPushButton(this);
  QIcon plusIcon = QIcon(":/graphics/Plus");
  boutonAddCue->setIcon(plusIcon);
  boutonAddCue->setFixedSize(80, 40);
  boutonAddCue->setIconSize(QSize(70, 30));

  boutonGo = new QPushButton(this);
  QIcon playIcon = QIcon(":/graphics/Play");
  boutonGo->setIcon(playIcon);
  boutonGo->setFixedSize(80, 40);
  boutonGo->setIconSize(QSize(70, 30));
  boutonGo->setShortcut(QKeySequence(Qt::Key_Space));

  boutonSaveAs = new QPushButton(this);
  QIcon saveIcon = QIcon(":/graphics/Save");
  boutonSaveAs->setIcon(saveIcon);
  boutonSaveAs->setFixedSize(80, 40);
  boutonSaveAs->setIconSize(QSize(70, 30));
  boutonSaveAs->setShortcut(QKeySequence("Ctrl+S"));

  boutonLoad = new QPushButton(this);
  QIcon loadIcon = QIcon(":/graphics/Load");
  boutonLoad->setIcon(loadIcon);
  boutonLoad->setFixedSize(80, 40);
  boutonLoad->setIconSize(QSize(70, 30));
  boutonLoad->setShortcut(QKeySequence("Ctrl+O"));


  boutonLayout->addWidget(boutonPrev);
  boutonLayout->addWidget(boutonNext);
  boutonLayout->addWidget(boutonRemove);
  boutonLayout->addWidget(boutonAddCue);
  boutonLayout->addWidget(boutonGo);
  boutonLayout->addWidget(boutonSaveAs);
  boutonLayout->addWidget(boutonLoad);

  treeView->setModel(m_oscCueList);
  m_delegate = new OscCuelistDelegate(this);
  treeView->setItemDelegate(m_delegate);
//  treeView->horizontalHeader()->setStretchLastSection(true);
//  treeView->verticalHeader()->setMaximumSectionSize(50);
  treeView->setTextElideMode(Qt::ElideLeft);
  treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

  treeView->show();
  layout1->addWidget(treeView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);

//  treeView->resizeColumnsToContents();
//  treeView->resizeRowsToContents();
  hideShowColumns();

  connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
  connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
  connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(remove()));
  connect(boutonAddCue, SIGNAL(clicked(bool)), SLOT(addCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
  connect(m_oscCueList, SIGNAL(dataChanged(QModelIndex, QModelIndex)), SLOT(hideShowColumns()));
  connect(midiIn2, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote2(int)));
}

void TabSeq::executeGo()
{
//  if (treeView->currentIndex().isValid())
//  {
//    int row = treeView->currentIndex().row();
//    if (m_oscCueList->isRowCue(row))  // Si c'est une cue sélectionnée...
//    {
//      tempCue = m_oscCueList->getOscCue(m_oscCueList->getCueId(row) - 1);
//      if (tempCue->oscSendCount()) // On vérifie que la cue a des sends
//      {
//        totalTime = tempCue->getTotalTime();
//        if (totalTime)
//        {
//          counter = 0;
//          QTimer::singleShot(totalTime, this, SLOT(timeProgressSteped()));
//        }
//        treeView->setCurrentIndex(treeView->currentIndex().siblingAtRow(treeView->currentIndex().row() + 1)); // on sélect le row suivant
//        connect(tempCue, SIGNAL(selectNextSend()), this, SLOT(selectNextRow()), Qt::UniqueConnection);
//        executeCue(tempCue);
//        qDebug() << "rowcount dans executeGo tabseq" << m_oscCueList->rowCount();
//      }
//    }
//    else // c'est un send
//    {
//      tempCue = m_oscCueList->getOscCue(m_oscCueList->getSendCueId(row) - 1); // On choppe la cue
//      tempSend = tempCue->getOscSend(m_oscCueList->getSendId(row) - 1); // On choppe le send
//      executeSend(tempSend); // on l'execute
//      treeView->setCurrentIndex(treeView->currentIndex().siblingAtRow(treeView->currentIndex().row() + 1)); // on sélect le row suivant
//    }
//  }
}

//void TabSeq::executeCue(OscCue *osccue)
//{
//  osccue->executeCue();
//}

void TabSeq::executeSend(OscSend *oscsend)
{
  oscsend->ExecuteSend();
}

void TabSeq::movePrevious() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = treeView->currentIndex();
  if (!index.isValid()) return;
  int row = index.row();
  if (m_oscCueList->isCue(index)) // Si c'est une cue
  {
    m_oscCueList->moveCuePrev(row);
    return;
  }
  // c'est un send
  m_oscCueList->moveSendPrev(index.parent().row(), row); // Seul blème l'index disparaît si on change de cue
//  if (row == 0)
//  {
    // faire index de la nouvelle cue parente et trouver le dernier row pour en créer un index...
//    treeView->setCurrentIndex(m_oscCueList.index()
//  }
  //  treeView->resizeRowsToContents();
//  treeView->resizeColumnsToContents();
}

void TabSeq::moveNext() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = treeView->currentIndex();
  if (!index.isValid()) return;
  int row = index.row();
  if (m_oscCueList->isCue(index)) // Si c'est une cue
  {
    m_oscCueList->moveCueNext(row);
    return;
  }
  // c'est un send
  m_oscCueList->moveSendNext(index.parent().row(), row); // Seul blème l'index disparaît si on change de cue
//  treeView->resizeColumnsToContents();
}

void TabSeq::remove()
{
  QModelIndex index = treeView->currentIndex();
  if (!index.isValid()) return;
  int row = index.row();
  if (m_oscCueList->isCue(index)) // Si c'est une cue
  {
    m_oscCueList->removeCue(row);
    return;
  }
  // c'est un send
  m_oscCueList->removeSend(index.parent().row(), row);
  hideShowColumns();
}

void TabSeq::addCue() // Reste à voir le sélectionné
{
  QModelIndex index = treeView->currentIndex();
  if (!index.isValid())
  {
    m_oscCueList->addCue();
    return;
  }
  if (m_oscCueList->isCue(index))
  {
    m_oscCueList->insertCue(index.row());
    return;
  }
  m_oscCueList->insertCue(index.parent().row() + 1);
  hideShowColumns();
}

void TabSeq::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Choose File", "", "Csv Files (*.csv *.txt)");
  if (fileName.isEmpty())
    return;
  else
  {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::information(this, "Unable to open file", file.errorString());
      return;
    }
    else
    {
      QString textData;
      int rows = m_oscCueList->rowCount();
      int columns = m_oscCueList->columnCount();

      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < columns; j++)
        {
            textData += m_oscCueList->data(m_oscCueList->index(i,j)).toString();
            textData += ", ";
        }
        textData += "\n";
      }
      QTextStream out(&file);
      out << textData;
      file.close();
    }
  }
}

void TabSeq::loadFile()
{
  QMessageBox msgBox(QMessageBox::Warning, "Load file warning",
                     "WARNING, this will destroy all cues", nullptr, this);
  msgBox.addButton(tr("OK"), QMessageBox::AcceptRole);
  msgBox.addButton(tr("CANCEL"), QMessageBox::RejectRole);
  if (msgBox.exec() == QMessageBox::RejectRole) return;

  QString fileName = QFileDialog::getOpenFileName(this, "Choose File", "", "Csv Files (*.csv *.txt)");
  QFile file(fileName);
  if (fileName.isEmpty()) return;

  if (file.open(QIODevice::ReadOnly))
  {
//    m_oscCueList->removeAllCue();
    int lineindex = 0;                     // file line counter
    QTextStream in(&file);                 // read to text stream
    while (!in.atEnd())
    {

      // read one line from textstream(separated by "\n")
      QString fileLine = in.readLine();
      // parse the read line into separate pieces(tokens) with "," as the delimiter
      QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
      QString firstVal = lineToken.at(0);
      firstVal = firstVal.trimmed();
      if (firstVal == "")
      {
//        OscCue *osccue = m_oscCueList->retOscCueFromFileLine(lineToken);
//        m_oscCueList->addCue(osccue);
      }
      else
      {
        OscSend *oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
//        m_oscCueList->addSend(oscsend, m_oscCueList->getLastCueRow());
      }
    }
    lineindex++;
  }
  file.close();
//  treeView->resizeRowsToContents();
//  treeView->resizeColumnsToContents();
  hideShowColumns();
}

void TabSeq::receiveMidiNote2(int note)
{
  if (!(note == 86)) return;
  boutonGo->animateClick();
  m_midiOut2->sendBoutonOn(86);
}

void TabSeq::timeProgressFinished()
{
  emit progressTimeFinished();
  counter = 0;
  totalTime = 0;
}

void TabSeq::timeProgressSteped()
{
  if (counter == 101)
  {
    timeProgressFinished();
    return;
  }
  counter++;
  emit updateProgressTime(counter);
  QTimer::singleShot(totalTime * 10, this, SLOT(timeProgressSteped()));
}

void TabSeq::selectNextRow()
{
  if (!treeView->currentIndex().isValid())
  {
    return;
  }
  if (!(treeView->currentIndex().row() == m_oscCueList->rowCount() - 1))
  {
    treeView->setCurrentIndex(treeView->currentIndex().siblingAtRow(treeView->currentIndex().row() + 1)); // on sélect le row suivant
  }
  else treeView->setCurrentIndex(treeView->currentIndex().siblingAtRow(0)); // on sélect le 1er row
}


void TabSeq::hideShowColumns()
{
  treeView->resizeColumnToContents(0);
  for (int i = P_name; i < Note; i++)
  {
    if (!m_oscCueList->hideShowColumn(i)) treeView->hideColumn(i);
    else treeView->showColumn(i);
    treeView->resizeColumnToContents(i);
  }
}

