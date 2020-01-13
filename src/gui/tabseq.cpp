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
               MyMidiOut *midiOut2
               ) :
  QWidget(),
  m_oscCueList(oscCueList),
  m_midiIn1(midiIn1),
  m_midiIn2(midiIn2),
  m_midiOut1(midiOut1),
  m_midiOut2(midiOut2),
  tableView(aTableView)
{
  layoutMain = new QHBoxLayout;
  layout1 = new QHBoxLayout;
  boutonLayout = new QVBoxLayout;
  boutonPrev = new QPushButton;
  boutonPrev->setText("<");
  boutonNext = new QPushButton;
  boutonNext->setText(">");
  boutonRemove = new QPushButton;
  boutonRemove->setText("-");
  boutonGo = new QPushButton;
  boutonGo->setText("GO !");
  boutonSaveAs = new QPushButton;
  boutonSaveAs->setText("Save As");
  boutonLoad = new QPushButton;
  boutonLoad->setText("Load");
  boutonLayout->addWidget(boutonPrev);
  boutonLayout->addWidget(boutonNext);
  boutonLayout->addWidget(boutonRemove);
  boutonLayout->addWidget(boutonGo);
  boutonLayout->addWidget(boutonSaveAs);
  boutonLayout->addWidget(boutonLoad);
  tableView = new TableView();
  tableView->setModel(m_oscCueList);

//  QCheckBox *checkbox_visible = new QCheckBox();
//  QItemDelegate *checkBoxDelegate = new QItemDelegate(checkbox_visible);
//  tableView->setItemDelegateForColumn(0, comboBoxDelegate); // Champ
//  tableView->setItemDelegateForColumn(3, fileDialogDelegate); // p_uri
//  tableView->setItemDelegateForColumn(4, colordialogDelegate); // p_color
//  tableView->setItemDelegateForColumn(14, checkBoxDelegate); // visible
//  tableView->setItemDelegateForColumn(15, checkBoxDelegate); // solo
//  tableView->setItemDelegateForColumn(16, checkBoxDelegate); // lock
//  tableView->setItemDelegateForColumn(18, checkBoxDelegate); // fadein
//  tableView->setItemDelegateForColumn(20, checkBoxDelegate); // wait

  tableView->show();
  tableView->resizeColumnsToContents();
  layout1->addWidget(tableView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);
//  setPalette(pal);

  connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
  connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
  connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(removeCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
}

void TabSeq::executeGo()
{
  tableView->resizeColumnsToContents();
  // Vérifier s'il y a une cue sélectionnée
  if (tableView->currentIndex().isValid())
  m_oscCueList->v_listCue.at((tableView->currentIndex().row()))->ExecuteSend();
  else
  {
    return;
  }
  if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid() == true)
  {
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1));
    // trouver pour afficher le nouveau select
//    tableView->selectRow(tableView->currentIndex().row());
    if (m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_iswaiting == 0)
    {
      usleep(1000000 * m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_time);
      std::cout << "wait " << m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_time << " s\n";
      executeGo();
    }
  }
  else tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(0));
}

void TabSeq::movePrevious()
{
  if (tableView->currentIndex().isValid())
  {
    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()-1).isValid())
    {
      m_oscCueList->moveCuePrev(tableView->currentIndex().row());
    }
  }
  tableView->resizeColumnsToContents();
}

void TabSeq::moveNext()
{
  if (tableView->currentIndex().isValid())
  {
    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid())
    {
      m_oscCueList->moveCuePrev(tableView->currentIndex().row() + 1);
    }
  }
  tableView->resizeColumnsToContents();
}

void TabSeq::removeCue()
{
  if (tableView->currentIndex().isValid())
  {
    m_oscCueList->removeCue(tableView->currentIndex().row());
  }
  tableView->resizeColumnsToContents();
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
      OscSend *oscsend = new OscSend(NOOP);
      int lineindex = 0;                     // file line counter
      QTextStream in(&file);                 // read to text stream
      while (!in.atEnd())
      {

        // read one line from textstream(separated by "\n")
        QString fileLine = in.readLine();
        // parse the read line into separate pieces(tokens) with "," as the delimiter
        QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
        oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
        m_oscCueList->addCue(oscsend);
      }
      lineindex++;
    }
    file.close();
    tableView->resizeColumnsToContents();
  }
}