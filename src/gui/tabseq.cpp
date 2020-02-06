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
               QTableView *aTableView,
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
  // On met une cue pour démarrer
  OscCue *firstCue = new OscCue(this);
  m_oscCueList->addCue(firstCue);

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

  proxyModel = new OscCueListProxy(m_oscCueList, this);
  proxyModel->setSourceModel(m_oscCueList);
  tableView->setModel(proxyModel);
  m_delegate = new OscCuelistDelegate(this);
  tableView->setItemDelegate(m_delegate);
//  tableView->horizontalHeader()->setMaximumSectionSize(200);
  tableView->horizontalHeader()->setStretchLastSection(true);
  tableView->verticalHeader()->setMaximumSectionSize(25);
  tableView->setTextElideMode(Qt::ElideRight);
  tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

  tableView->show();
  layout1->addWidget(tableView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);

  tableView->resizeColumnsToContents();
  tableView->resizeRowsToContents();
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
        /*if (!timeWait) QTimer::singleShot(10, this, SLOT(executeGo())); // Si timeWait 0 on attend 10ms et on éxécute le prochain
        else*/ QTimer::singleShot((100 * (int)(timeWait*10)) + 1, this, SLOT(executeGo())); // On attend le timeWait et on éxécute le prochain
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
  tableView->resizeRowsToContents();
  tableView->resizeColumnsToContents();
}

void TabSeq::moveNext() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = tableView->currentIndex();
  int row = index.row();
//  qDebug() << "row selected" << row;
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
  tableView->resizeRowsToContents();
  tableView->resizeColumnsToContents();
}

void TabSeq::remove() // Bouger cue si c'est une cue, bouger send si c'est un send
{
  QModelIndex index = tableView->currentIndex();
  int row = index.row();
//  qDebug() << "row selected" << row;
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
  else tableView->setCurrentIndex(m_oscCueList->index(row - 1, 0)); // ça c'est plus simple que table view et cie
  tableView->resizeRowsToContents();
  tableView->resizeColumnsToContents();
  hideShowColumns();
}

void TabSeq::addCue() // Reste à voir le sélectionné // TODO rajouter index = currentindex et row ça sera plus simple
{
  OscCue *newCue = new OscCue(this);
  if (!tableView->currentIndex().isValid() || tableView->currentIndex().row() == m_oscCueList->rowCount() - 1)
  {
    m_oscCueList->addCue(newCue);
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(m_oscCueList->rowCount() - 1));
  }
  else if (m_oscCueList->isRowCue(tableView->currentIndex().row()))
  {
    m_oscCueList->insertCue(newCue, tableView->currentIndex().row());
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(m_oscCueList->getRowCueFromCueId(m_oscCueList->getCueId(tableView->currentIndex().row()) - 1)));
  }
  else // send sélectionné
  {
    int sendCueId = m_oscCueList->getSendCueId(tableView->currentIndex().row());
    m_oscCueList->insertCue(newCue, m_oscCueList->getRowCueFromCueId(sendCueId + 1));
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row() + 1)); // pas bon
  }
  tableView->resizeRowsToContents();
  tableView->resizeColumnsToContents();
  hideShowColumns();
}

void TabSeq::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Choose File", "", "Csv Files (*.csv *.txt)");
  if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::information(this, "Unable to open file", file.errorString());
      return;
    }
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
      QTextStream out(&file);
      out << textData;
      file.close();
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
    m_oscCueList->removeAllCue();
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
        OscCue *osccue = m_oscCueList->retOscCueFromFileLine(lineToken);
        m_oscCueList->addCue(osccue);
      }
      else
      {
        OscSend *oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
        m_oscCueList->addSend(oscsend, m_oscCueList->getLastCueRow());
      }
    }
    lineindex++;
  }
  file.close();
  tableView->resizeRowsToContents();
  tableView->resizeColumnsToContents();
  hideShowColumns();
}

void TabSeq::receiveMidiNote2(int note)
{
  if (!(note == 86)) return;
  boutonGo->animateClick();
  m_midiOut2->sendBoutonOn(86);
}

void TabSeq::hideShowColumns()
{
//  int rows = m_oscCueList->rowCount();
  for(int i = P_name; i < Wait; i++)
  {
    QString textData;
    for(int j = 0; j < m_oscCueList->rowCount(); j++)
    {
      textData += m_oscCueList->data(m_oscCueList->index(j, i)).toString();
    }
    if (!textData.size()) tableView->hideColumn(i);
    else tableView->showColumn(i);
  }
}

