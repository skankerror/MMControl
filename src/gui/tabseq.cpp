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
               TableView *aTableView,
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
  tableView(aTableView)
{
  // pour tester
//  OscSend *oscsend = new OscSend(this, P_OPACITY);
//  oscsend->setP_ID1(2);
//  oscsend->setP_opacity(80);
//  oscsend->setTimewait(1.0);
//  OscSend *oscsend2 = new OscSend(this ,PAUSE);
//  OscCue *osccue = new OscCue(this);
//  OscSend *oscsend3 = new OscSend(this, REWIND);
//  OscCue *osccue2 = new OscCue(this);
//  OscSend *oscsend4 = new OscSend(this, PLAY);
//  OscCue *osccue3 = new OscCue(this);
//  osccue->addOscSend(oscsend);
//  osccue->addOscSend(oscsend2);
//  m_oscCueList->addCue(osccue);
//  osccue2->addOscSend(oscsend3);
//  m_oscCueList->addCue(osccue2);
//  osccue3->addOscSend(oscsend4);
//  m_oscCueList->addCue(osccue3);
//  qDebug() << "number of cue : " << m_oscCueList->getOscCueCount();
//  qDebug() << "row count : " << m_oscCueList->rowCount();
//  qDebug() << "column count : " << m_oscCueList->columnCount();
//  for (int i = 0; i < m_oscCueList->rowCount(); i++)
//  {
//    qDebug() << "Row " << i << m_oscCueList->isRowCue(i);
//  }
//  for (int i = 0; i < m_oscCueList->rowCount(); i++)
//  {
//    if (m_oscCueList->isRowCue(i)) qDebug() << "Row" << i << "getCueId" << m_oscCueList->getCueId(i);
//    else
//    {
//      qDebug() << "Row" << i <<
//                  "getSendCueId" << m_oscCueList->getSendCueId(i) <<
//                  "getSendId" << m_oscCueList->getSendId(i);
//    }
//  }
//  OscSend *oscsendToAdd = new OscSend(this, NOOP);
//  m_oscCueList->addSend(oscsendToAdd, 3);
//  for (int i = 0; i < m_oscCueList->getOscCueCount(); i++)
//  {
//    qDebug() << "cueId" << i + 1 << "row" << m_oscCueList->getRowCueFromCueId(i + 1);
//  }
//  OscSend *oscsendToInsert = new OscSend(this, QUIT);
//  m_oscCueList->insertSend(oscsendToInsert, 5);
//  m_oscCueList->moveSendPrev(3);
//  m_oscCueList->removeSend(1);
////  m_oscCueList->removeAllSend(0);
//  OscCue *osccueToInsert = new OscCue(this);
//  m_oscCueList->insertCue(osccueToInsert, 0);
//  m_oscCueList->moveCuePrev(1);
//  m_oscCueList->removeCue(0);
//  m_oscCueList->removeAllCue();
  // fin test

  // On met une cue pour démarrer
  OscCue *firstCue = new OscCue(this);
  m_oscCueList->addCue(firstCue);

  layoutMain = new QHBoxLayout(this);
  layout1 = new QHBoxLayout(this);
  boutonLayout = new QVBoxLayout(this);
  boutonPrev = new QPushButton(this);
  boutonPrev->setText("<");
  boutonNext = new QPushButton(this);
  boutonNext->setText(">");
  boutonRemove = new QPushButton(this);
  boutonRemove->setText("-");
  boutonAddCue = new QPushButton(this);
  boutonAddCue->setText("Add Cue");
  boutonGo = new QPushButton(this);
  boutonGo->setText("GO !");
  boutonSaveAs = new QPushButton(this);
  boutonSaveAs->setText("Save As");
  boutonLoad = new QPushButton(this);
  boutonLoad->setText("Load");
  boutonLayout->addWidget(boutonPrev);
  boutonLayout->addWidget(boutonNext);
  boutonLayout->addWidget(boutonRemove);
  boutonLayout->addWidget(boutonAddCue);
  boutonLayout->addWidget(boutonGo);
  boutonLayout->addWidget(boutonSaveAs);
  boutonLayout->addWidget(boutonLoad);

  tableView->setModel(m_oscCueList);
  m_delegate = new OscCuelistDelegate(this);
  tableView->setItemDelegate(m_delegate);

  tableView->show();
  tableView->resizeColumnsToContents();
  tableView->resizeRowsToContents();
  layout1->addWidget(tableView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);

  connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
  connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
  connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(remove()));
  connect(boutonAddCue, SIGNAL(clicked(bool)), SLOT(addCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
}

void TabSeq::executeGo()
{
  int row = tableView->currentIndex().row();
  if (tableView->currentIndex().isValid())
  {
    if (m_oscCueList->isRowCue(row))  // Si c'est une cue sélectionnée...
    {
      if (m_oscCueList->getOscCue(m_oscCueList->getCueId(row) - 1)->oscSendCount()) // On vérifie que la cue a des sends
      {
        tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(row + 1)); // On sélectionne le 1er send
        executeGo(); // Et on l'éxécute (pourquoi tant de haine ?)
      }
    }
    else // C'est un send
    {
      OscCue *tempCue = m_oscCueList->getOscCue(m_oscCueList->getSendCueId(row) - 1); // On choppe la cue parente
      OscSend *tempSend = tempCue->getOscSend(m_oscCueList->getSendId(row) - 1); // On choppe le bon send...
      tempSend->ExecuteSend(); // On éxécute
      double timeWait = tempSend->getTimewait(); // on choppe le temps d'attente
      tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row() + 1)); // on sélect le row suivant
      if (!m_oscCueList->isRowCue(tableView->currentIndex().row()))// Si c'est un send
      {
        QTimer::singleShot(100 * (int)(timeWait*10), this, SLOT(executeGo())); // On attend le timeWait et on éxécute le prochain
      }
    }
  }
}

void TabSeq::movePrevious() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = tableView->currentIndex();
  int row = index.row();
  qDebug() << "row selected" << row;
  if (!index.isValid() || row < 1 /* Si c'est 0 on peut pas remonter */ || row > m_oscCueList->rowCount()) return;
  if (m_oscCueList->isRowCue(row)) // Si c'est une cue
  {
    int cueId = m_oscCueList->getCueId(row); // on garde en mémoire l'id de la cue pour la sélectionner après
    m_oscCueList->moveCuePrev(row);
    int rowCueNewId = m_oscCueList->getRowCueFromCueId(cueId - 1); // on récupère son nouveau row
    tableView->setCurrentIndex(m_oscCueList->index(rowCueNewId, 0)); // on le sélectionne
  }
  else // c'est un send
  {
    int sendId = m_oscCueList->getSendId(row);
    int cueId = m_oscCueList->getSendCueId(row);
    m_oscCueList->moveSendPrev(row);
    if (sendId == 1 && cueId > 1) // Si on a bougé de cue
      tableView->setCurrentIndex(m_oscCueList->index(row - 1, 0)); // on le resélectionne
  }
//  tableView->resizeRowsToContents();
//  tableView->resizeColumnsToContents();
}

void TabSeq::moveNext() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = tableView->currentIndex();
  int row = index.row();
  qDebug() << "row selected" << row;
  if (!index.isValid() || row > m_oscCueList->rowCount() - 2) return; // Si c'est le dernier row on fait rien...
  if (m_oscCueList->isRowCue(row)) // Si c'est une cue
  {
    int cueId = m_oscCueList->getCueId(row);
    int cueCount = m_oscCueList->getOscCueCount();
    if (cueId >= cueCount) return; // on pourra pas faire next
    int rowNextCue = m_oscCueList->getRowCueFromCueId(cueId + 1); // On récupère le row de la next cue
    m_oscCueList->moveCuePrev(rowNextCue);
    rowNextCue = m_oscCueList->getRowCueFromCueId(cueId + 1); // On reprend le row de notre cue boougée
    tableView->setCurrentIndex(m_oscCueList->index(rowNextCue, 0)); // On le sélectionne
  }
  else // c'est un send
  {
    m_oscCueList->moveSendNext(row);
  }
  //  tableView->resizeRowsToContents();
  //  tableView->resizeColumnsToContents();
}

void TabSeq::remove() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = tableView->currentIndex();
  int row = index.row();
  qDebug() << "row selected" << row;
  if (!index.isValid() || row > m_oscCueList->rowCount() - 1) return;
  if (m_oscCueList->isRowCue(row))
  {
    m_oscCueList->removeCue(row);
  }
  else
  {
    m_oscCueList->removeSend(row);
  }
  if (!row) tableView->setCurrentIndex(m_oscCueList->index(0, 0));
  else tableView->setCurrentIndex(m_oscCueList->index(row - 1, 0));
//  tableView->resizeRowsToContents();
//  tableView->resizeColumnsToContents();
}

void TabSeq::addCue() // Rest ça à refaire...
{
  OscCue *newCue = new OscCue(this);
  if (!tableView->currentIndex().isValid())
  {
    m_oscCueList->addCue(newCue);
  }
  else if (m_oscCueList->isRowCue(tableView->currentIndex().row())) // Si c'est une cue
  {
    m_oscCueList->insertCue(newCue, tableView->currentIndex().row());
  }
  else
  {

  }
}

void TabSeq::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Choose File", "/home/ray/boulot");
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
  else
  {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose File", "/home/ray/boulot");
    QFile file(fileName);
    if (fileName.isEmpty())
    {
      return;
    }
    if (file.open(QIODevice::ReadOnly))
    {
      m_oscCueList->removeAllCue();
//      OscSend *oscsend = new OscSend(this, NOOP);
      int lineindex = 0;                     // file line counter
      QTextStream in(&file);                 // read to text stream
      while (!in.atEnd())
      {

        // read one line from textstream(separated by "\n")
        QString fileLine = in.readLine();
        // parse the read line into separate pieces(tokens) with "," as the delimiter
        QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
//        oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
//        m_oscCueList->addCue(oscsend); // à refaire
      }
      lineindex++;
    }
    file.close();
//    tableView->resizeRowsToContents();
//    tableView->resizeColumnsToContents();
  }
}

