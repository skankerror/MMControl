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
  m_oscCueList->addCue();

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
  treeView->setTextElideMode(Qt::ElideLeft);
  treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
//  treeView->setAutoFillBackground(true);

  treeView->show();
  layout1->addWidget(treeView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);

  hideShowColumns();

  timerWait = new QTimer(this);

  connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
  connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
  connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(remove()));
  connect(boutonAddCue, SIGNAL(clicked(bool)), SLOT(addCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
  connect(m_oscCueList, SIGNAL(dataChanged(QModelIndex, QModelIndex)), SLOT(hideShowColumns()));
  connect(treeView, SIGNAL(expanded(QModelIndex)), this, SLOT(hideShowColumns()));
  connect(midiIn2, SIGNAL(sigMidiNoteChanged(int)), this, SLOT(receiveMidiNote2(int)));
  connect(timerWait, SIGNAL(timeout()), this, SLOT(timeWaitProgressStepedSend()));
}

void TabSeq::executeGo()
{
  QModelIndex index = treeView->currentIndex();
  if (!index.isValid()) return;
  if (m_oscCueList->isCue(index)) // Si c'est une cue
  {
    OscSend *tempCue = m_oscCueList->getSend(index); // On la choppe
    if (!tempCue->getSendCount()) // Si elle est vide
    {
      // On sélectionne la cue d'après
      QModelIndex newIndex = index.siblingAtRow(index.row() + 1);
      // Si pas valide on sélect la 1ère cue
      if (!newIndex.isValid()) treeView->setCurrentIndex(index.siblingAtRow(0));
      else treeView->setCurrentIndex(newIndex); // On sélect la suivante
      return; // on quitte
    }
    totalTime = tempCue->getTimewait();
    if (totalTime)
    {
      counterCue = 0;
      QTimer::singleShot(totalTime, this, SLOT(timeProgressStepedCue()));
    }
    treeView->setCurrentIndex(m_oscCueList->index(0, 0, index));
    executeGo();
    return;
  }
  // C'est un send;
  tempSend = m_oscCueList->getSend(index);
  connect(tempSend, SIGNAL(sendStringToOutputLabel(QString)), this, SLOT(receiveStringFromSend(QString)), Qt::UniqueConnection);
  executeSend(tempSend);
  // On gère le time
  int champ = tempSend->getChamp();
  waitTimeSend = tempSend->getTimewait();
  if (champ == P_FADE || champ == P_XFADE || champ == R_P_FADE || champ == R_P_XFADE)
  {
    fadeTimeSend = tempSend->getTime();
  }
  else fadeTimeSend = 0;
  totalTimeSend = waitTimeSend + fadeTimeSend;
  if (fadeTimeSend)
  {
    // on lance le timer du fade et lui-même lancera le timer du wait si besoin
    counterSend = 0;
    QTimer::singleShot(totalTimeSend, this, SLOT(timeProgressStepedSend()));
  }
  else if (waitTimeSend) // Sinon on lance le timerwait si besoin
  {
    counterSendWait = 0;
    sendWaitToOutputLabel();
    timerWait->start(waitTimeSend * 10);
  }
  // Puis timer total pour passer au row suivant
  QTimer::singleShot((100 * (int)(totalTimeSend*10)) + 1, this, SLOT(selectRow()));
  return;
}

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
  if (m_oscCueList->moveSendPrev(index.parent().row(), row)) // Si true on a changé de cue
  {
    // Sélectionner le nouveau row
    QModelIndex indexNewCue = index.parent().siblingAtRow(index.parent().row() - 1);
    int newRow = m_oscCueList->getSend(indexNewCue)->getSendCount() - 1;
    treeView->setCurrentIndex(m_oscCueList->index(newRow, 0, indexNewCue));
  }
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
  if (m_oscCueList->moveSendNext(index.parent().row(), row)) // si true on a changé de cue
  {
    // Sélectionner le nouveau row
    QModelIndex indexNewCue = index.parent().siblingAtRow(index.parent().row() + 1);
    treeView->setCurrentIndex(m_oscCueList->index(0, 0, indexNewCue));
  }
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
        // boucle pour les fils
        int rowsChild = m_oscCueList->rowCount(m_oscCueList->index(i, 0));
        for (int k = 0; k < rowsChild; k++)
        {
          for (int l = 0; l < columns; l++)
          {
            textData += m_oscCueList->data(m_oscCueList->index(k, l, m_oscCueList->index(i, 0))).toString();
            textData += ", ";
          }
          textData += "\n";
        }
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
    m_oscCueList->removeAllCue();
    int lineindex = 0;                     // file line counter
    QTextStream in(&file);                 // read to text stream
    while (!in.atEnd())
    {
      // Attention on ne vérifie rien sur le contenu du fichier
      // read one line from textstream(separated by "\n")
      QString fileLine = in.readLine();
      // parse the read line into separate pieces(tokens) with "," as the delimiter
      QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
      QString firstVal = lineToken.at(0);
      firstVal = firstVal.trimmed();
      firstVal.resize(3);

      if (firstVal == "CUE") // c'est une CUE
      {
        m_oscCueList->addCueFromFileLine(lineToken);
      }
      else
      {
        OscSend *oscsend = m_oscCueList->retOscsendFromFileLine(lineToken);
        int lastCue = m_oscCueList->rowCount() - 1;
        m_oscCueList->addSend(oscsend, lastCue);
      }
    }
    lineindex++;
  }
  file.close();
  hideShowColumns();
}

void TabSeq::receiveMidiNote2(int note)
{
  if (!(note == 86)) return;
  boutonGo->animateClick();
  m_midiOut2->sendBoutonOn(86);
}

void TabSeq::timeProgressFinishedCue()
{
  emit progressTimeFinishedCue();
  counterCue = 0;
  totalTime = 0;
}

void TabSeq::timeProgressStepedCue()
{
  if (counterCue == 101)
  {
    timeProgressFinishedCue();
    return;
  }
  counterCue++;
  emit updateProgressTimeCue(counterCue);
  QTimer::singleShot(totalTime * 10, this, SLOT(timeProgressStepedCue()));
}

void TabSeq::timeProgressFinishedSend()
{
  emit progressTimeFinishedSend();
  counterSend = 0;
  fadeTimeSend = 0;
  if (waitTimeSend)
  {
    counterSendWait = 0;
    sendWaitToOutputLabel();
    timerWait->start(waitTimeSend * 10);
  }
}

void TabSeq::timeProgressStepedSend()
{
  if (counterSend == 101)
  {
    timeProgressFinishedSend();
    return;
  }
  counterSend++;
  emit updateProgressTimeSend(counterSend);
  QTimer::singleShot(fadeTimeSend * 10, this, SLOT(timeProgressStepedSend()));
}

void TabSeq::timeWaitProgressFinishedSend()
{
  emit progressTimeWaitFinishedSend();
  counterSendWait = 0;
  waitTimeSend = 0;
  if (timerWait->isActive()) timerWait->stop();
}

void TabSeq::timeWaitProgressStepedSend()
{
  if (counterSendWait == 101)
  {
    timeWaitProgressFinishedSend();
    return;
  }
  counterSendWait++;
  sendWaitToOutputLabel();
  emit updateProgressTimeWaitSend(counterSendWait);
}

void TabSeq::selectRow()
{
  QModelIndex index = treeView->currentIndex(); // On choppe l'index courant
  QModelIndex newIndex = index.siblingAtRow(index.row() + 1); // On choppe le send suivant
  if (newIndex.isValid()) // S'il existe
  {
    emit progressTimeWaitFinishedSend(); // On coupe le timer
    counterSendWait = 0;
    waitTimeSend = 0;
    if (timerWait->isActive()) timerWait->stop();
    emit progressTimeFinishedSend(); // on coupe le timer
    counterSend = 0;
    fadeTimeSend = 0;
    treeView->setCurrentIndex(index.siblingAtRow(index.row() + 1));
    executeGo();
    return;
  }
  else //Sinon c'est une cue
  {
    newIndex = index.parent().siblingAtRow(index.parent().row() + 1); // On la sélectionne
    //Si elle existe pas on prend la 1ère
    if (!newIndex.isValid()) treeView->setCurrentIndex(index.parent().siblingAtRow(0));
    else treeView->setCurrentIndex(newIndex); // Sinon on la sélectionne
    emit progressTimeFinishedCue(); // on coupe le timer de la cue
    counterCue = 0;
    totalTime = 0;
    resetOutputLabel();
  }
}

void TabSeq::receiveStringFromSend(QString tempString)
{
  emit sendStringToOutputLabel(tempString);
}

void TabSeq::sendWaitToOutputLabel()
{
  emit sendStringToOutputLabel(QString("Wait -->"));
  //  qDebug() << "Wait";
}

void TabSeq::resetOutputLabel()
{
  emit sendStringToOutputLabel(QString(""));
}

void TabSeq::hideShowColumns()
{
  treeView->resizeColumnToContents(Champ);
  treeView->resizeColumnToContents(Wait);
  for (int i = P_name; i < Wait; i++)
  {
    if (!m_oscCueList->hideShowColumn(i)) treeView->hideColumn(i);
    else treeView->showColumn(i);
    treeView->resizeColumnToContents(i);
  }
}

