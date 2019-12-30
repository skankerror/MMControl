#include "tabseq.h"

TabSeq::TabSeq(OscCueList *oscCueList) :
  QWidget(),
  m_oscCueList(oscCueList)
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
  tableView = new QTableView();
  tableView->setModel(oscCueList);
  tableView->show();
  tableView->resizeColumnsToContents();
  layout1->addWidget(tableView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
  connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
  connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
  connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(removeCue()));
  connect(boutonSaveAs, SIGNAL(clicked(bool)), SLOT(saveAs()));
  connect(boutonLoad, SIGNAL(clicked(bool)), SLOT(loadFile()));
}

void TabSeq::executeGo()
{
  m_oscCueList->v_listCue.at((tableView->currentIndex().row()))->ExecuteSend();
  if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid() == true)
  {
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1));
    if (m_oscCueList->v_listCue.at((tableView->currentIndex().row()-1))->m_iswaiting == false)
    {
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
}

void TabSeq::removeCue()
{
  if (tableView->currentIndex().isValid())
  {
    m_oscCueList->removeCue(tableView->currentIndex().row());
  }
}

void TabSeq::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save cuelist", "", "csv File(.csv);;All files (*)");
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
//  QString fileName = QFileDialog::getOpenFileName(this, "Load cuelist", "", "csv File(.csv);;All files (*)" );
//  //if (fileName.isEmpty())
//  //  return;
//  //else
//  //{
//    QFile file(fileName);
//    int lineindex = 0;
//    QTextStream in(&file);

//    while (!in.atEnd())
//    {
//      QString fileLine = in.readLine();
//      QStringList lineToken = fileLine.split(",");
//      for (int j = 0; j < lineToken.size(); j++)
//      {
//        QString value = lineToken.at(j);
//        QStandardItem *item = new QStandardItem(value);
//        std::cout << value.toStdString() << std::endl;
//        m_oscCueList->setData(m_oscCueList->index(lineindex, j), value);
//      }
//      lineindex++;
//    }
//    file.close();
//  //}
}
