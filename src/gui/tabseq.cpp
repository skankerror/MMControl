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
  OscSend *oscsend = new OscSend(this, P_OPACITY);
  oscsend->setP_ID1(2);
  oscsend->setP_opacity(80);
  oscsend->setTimewait(1.0);
  OscSend *oscsend2 = new OscSend(this ,PAUSE);
  OscCue *osccue = new OscCue(this);
  OscSend *oscsend3 = new OscSend(this, REWIND);
  OscCue *osccue2 = new OscCue(this);
  OscSend *oscsend4 = new OscSend(this, PLAY);
  OscCue *osccue3 = new OscCue(this);
  osccue->addOscSend(oscsend);
  osccue->addOscSend(oscsend2);
  m_oscCueList->addCue(osccue);
  osccue2->addOscSend(oscsend3);
  m_oscCueList->addCue(osccue2);
  osccue3->addOscSend(oscsend4);
  m_oscCueList->addCue(osccue3);
  qDebug() << "number of cue : " << m_oscCueList->getOscCueCount();
//  qDebug() << "number of event : " << m_oscCueList->getOscCue(0)->oscSendCount() << m_oscCueList->getOscCue(1)->oscSendCount();
  qDebug() << "row count : " << m_oscCueList->rowCount();
  qDebug() << "column count : " << m_oscCueList->columnCount();
  for (int i = 0; i < m_oscCueList->rowCount(); i++)
  {
    qDebug() << "Row " << i << m_oscCueList->isRowCue(i);
  }
  for (int i = 0; i < m_oscCueList->rowCount(); i++)
  {
    if (m_oscCueList->isRowCue(i)) qDebug() << "Row" << i << "getCueId" << m_oscCueList->getCueId(i);
    else
    {
      qDebug() << "Row" << i <<
                  "getSendCueId" << m_oscCueList->getSendCueId(i) <<
                  "getSendId" << m_oscCueList->getSendId(i);

    }
  }
//  qDebug() << "getSendId(6)" << m_oscCueList->getSendId(6);
//  qDebug() << "getSendCueId(6)" << m_oscCueList->getSendCueId(6);
//  qDebug() << oscsend->getChamp();
//  qDebug() << oscsend2->getChamp();
//  qDebug() << oscsend3->getChamp();

  layoutMain = new QHBoxLayout(this);
  layout1 = new QHBoxLayout(this);
  boutonLayout = new QVBoxLayout(this);
  boutonPrev = new QPushButton(this);
  boutonPrev->setText("<");
  boutonNext = new QPushButton(this);
  boutonNext->setText(">");
  boutonRemove = new QPushButton(this);
  boutonRemove->setText("-");
  boutonGo = new QPushButton(this);
  boutonGo->setText("GO !");
  boutonSaveAs = new QPushButton(this);
  boutonSaveAs->setText("Save As");
  boutonLoad = new QPushButton(this);
  boutonLoad->setText("Load");
  boutonLayout->addWidget(boutonPrev);
  boutonLayout->addWidget(boutonNext);
  boutonLayout->addWidget(boutonRemove);
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
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(removeCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
}

void TabSeq::executeGo()
{
////  tableView->resizeColumnsToContents();
////  tableView->resizeRowsToContents();
//  // Vérifier s'il y a une cue sélectionnée
//  if (treeView->currentIndex().isValid())
//  m_oscCueList->v_listCue.at((treeView->currentIndex().row()))->ExecuteSend();
//  else
//  {
//    return;
//  }
//    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid() == true)
//  {
//    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1));
//    double timeWait = m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_timeWait;
//    if (timeWait > 0)
//    {
//      qDebug() << "wait " << m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_timeWait << " s";
//      QTimer::singleShot(100 * (int)(timeWait*10), this, SLOT(executeGo()));
//    }
//  }
//  else tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(0));
}

void TabSeq::movePrevious()
{
//  if (tableView->currentIndex().isValid())
//  {
//    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()-1).isValid())
//    {
//      m_oscCueList->moveCuePrev(tableView->currentIndex().row());
//    }
//  }
//  tableView->resizeRowsToContents();
//  tableView->resizeColumnsToContents();
}

void TabSeq::moveNext()
{
//  if (tableView->currentIndex().isValid())
//  {
//    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid())
//    {
//      m_oscCueList->moveCuePrev(tableView->currentIndex().row() + 1);
//    }
//  }
//  tableView->resizeRowsToContents();
//  tableView->resizeColumnsToContents();
}

void TabSeq::removeCue()
{
//  if (tableView->currentIndex().isValid())
//  {
//    m_oscCueList->removeCue(tableView->currentIndex().row());
//  }
//  tableView->resizeRowsToContents();
//  tableView->resizeColumnsToContents();
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
      OscSend *oscsend = new OscSend(this, NOOP);
      int lineindex = 0;                     // file line counter
      QTextStream in(&file);                 // read to text stream
      while (!in.atEnd())
      {

        // read one line from textstream(separated by "\n")
        QString fileLine = in.readLine();
        // parse the read line into separate pieces(tokens) with "," as the delimiter
        QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
        oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
//        m_oscCueList->addCue(oscsend); // à refaire
      }
      lineindex++;
    }
    file.close();
//    tableView->resizeRowsToContents();
//    tableView->resizeColumnsToContents();
  }
}
