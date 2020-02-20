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

#include "tabmmstate.h"

TabMMState::TabMMState(MMStateList *stateList, QWidget *parent) :
  QWidget(parent),
  m_stateList(stateList)
{
  treeView = new QTreeView(this);

  layoutMain = new QVBoxLayout();

  createToolBar();
  typeSelected(0);

  treeView->setModel(m_stateList);
  treeView->setTextElideMode(Qt::ElideLeft);
  treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

  treeView->show();

  layoutMain->addLayout(layoutBar);
  layoutMain->addWidget(treeView);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);
}

void TabMMState::typeSelected(const int index)
{
  if (index == 0)
  {
      nameLine->setText("Paint");
    paintTypeBox->show();
      paintTypeBox->setCurrentIndex(0);
    uriLabel->show();
      uriLabel->setText("Choose->");
    uriButton->show();
    colorLabel->hide();
    colorButton->hide();
    cameraLabel->hide();
    cameraButton->hide();
      opacityBox->setValue(0);
    rateLabel->show();
    rateBox->show();
      rateBox->setValue(100);
    volumeLabel->show();
    volumeBox->show();
      volumeBox->setValue(100);
    visibleBox->hide();
    soloBox->hide();
    lockBox->hide();
    depthLabel->hide();
    depthBox->hide();
  }
  if (index == 1)
  {
      nameLine->setText("Mesh");
    paintTypeBox->hide();
    uriLabel->hide();
    uriButton->hide();
    colorLabel->hide();
    colorButton->hide();
    cameraLabel->hide();
    cameraButton->hide();
      opacityBox->setValue(100);
    rateLabel->hide();
    rateBox->hide();
    volumeLabel->hide();
    volumeBox->hide();
    visibleBox->show();
      visibleBox->setChecked(false);
    soloBox->show();
      soloBox->setChecked(false);
    lockBox->show();
      lockBox->setChecked(true);
    depthLabel->show();
    depthBox->show();
  }
  return;
}

void TabMMState::paintTypeSelected(const int index)
{
  switch (index)
  {
  case videoPaint:
    uriLabel->show();
      uriLabel->setText("Choose->");
    uriButton->show();
    colorLabel->hide();
    colorButton->hide();
    cameraLabel->hide();
    cameraButton->hide();
    break;
  case colorPaint:
    colorLabel->show();
      colorLabel->setText("Choose->");
    colorButton->show();
    uriLabel->hide();
    uriButton->hide();
    cameraLabel->hide();
    cameraButton->hide();
    break;
  case cameraPaint:
    cameraLabel->show();
      cameraLabel->setText("Choose->");
    cameraButton->show();
    colorLabel->hide();
    colorButton->hide();
    uriLabel->hide();
    uriButton->hide();
    break;
  default: break;
  }
}

void TabMMState::addToState()
{
  if (typeBox->currentIndex() == 0)
  {
    MMPaint *paint = new MMPaint(this);
    paint->setM_id(idBox->value());
    paint->setM_name(nameLine->text());
    int paintType = paintTypeBox->currentIndex();
    paint->setM_paintType(paintTypeBox->currentIndex());
    switch (paintType)
    {
    case videoPaint:
      while (uriLabel->text() == "Choose->") setUriLabel();
      paint->setM_uri(uriLabel->text());
      break;
    case colorPaint:
      while (colorLabel->text() == "Choose->") setColorLabel();
      paint->setM_uri(colorLabel->text());
      break;
    case cameraPaint:
      while (cameraLabel->text() == "Choose->") setCameraLabel();
      paint->setM_uri(cameraLabel->text());
      break;
    default: break;
    }
    paint->setM_opacity(opacityBox->value());
    paint->setM_rate(rateBox->value());
    paint->setM_volume(volumeBox->value());
    m_stateList->addPaint(paint, 0); // voir pour l'insert ?
  }
  else
  {
    MMMapping *mapping = new MMMapping(this);
    mapping->setM_id(idBox->value());
    mapping->setM_name(nameLine->text());
    mapping->setM_opacity(opacityBox->value());
    mapping->setVisible(visibleBox->isChecked());
    mapping->setSolo(soloBox->isChecked());
    mapping->setLocked(lockBox->isChecked());
    mapping->setM_depth(depthBox->value());
    // voir le paint sélectionné
    QModelIndex indexSelected = treeView->currentIndex();
    int lastPaintRow = m_stateList->getState(0)->getPaintCount() - 1;
    if (!indexSelected.isValid())
    {
      m_stateList->addMapping(mapping, 0, lastPaintRow);
      return;
    }
    QObject *item = m_stateList->getItem(indexSelected);
    QString className = item->metaObject()->className();
    if (className == "MMState")
    {
      m_stateList->addMapping(mapping, 0, lastPaintRow);
      return;
    }
    if (className == "MMPaint")
    {
      m_stateList->addMapping(mapping, 0, indexSelected.row());
      return;
    }
    if (className == "MMMapping")
    {
      m_stateList->addMapping(mapping, 0, indexSelected.parent().row());
      return;
    }
  }
}

void TabMMState::setUriLabel()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Choose File", "",
                                                  "Media Files (*.png *.jpg *.gif *.tif *.mov *.avi *.mp4)");
  uriLabel->setText(fileName);
}

void TabMMState::setColorLabel()
{
  QColor colorTemp = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
  colorLabel->setText(colorTemp.name());
}

void TabMMState::setCameraLabel()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Choose device", "/dev", "");
  cameraLabel->setText(fileName);
}

void TabMMState::saveAs()
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
      QModelIndex indexParent = m_stateList->index(0, 0); // index du state 1
      QString textData;
      int rows = m_stateList->rowCount(indexParent);
      int columns = m_stateList->columnCount();

      for (int i = 0; i < rows; i++)
      {
        // boucle pour les paints
        textData += "PAINT";
        textData += ", ";
        for (int j = 0; j < columns; j++)
        {
            textData += m_stateList->data(m_stateList->index(i,j, indexParent)).toString();
            textData += ", ";
        }
        textData += "\n";
        // boucle pour les Mapping
        int rowsChild = m_stateList->rowCount(m_stateList->index(i, 0, indexParent));
        for (int k = 0; k < rowsChild; k++)
        {
          textData += "MAPPING";
          textData +=", ";
          for (int l = 0; l < columns; l++)
          {
            textData += m_stateList->data(m_stateList->index(k, l, m_stateList->index(i, 0, indexParent))).toString();
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

void TabMMState::loadFile()
{
  QMessageBox msgBox(QMessageBox::Warning, "Load file warning",
                     "WARNING, this will destroy actual state", nullptr, this);
  msgBox.addButton("OK", QMessageBox::AcceptRole);
  msgBox.addButton("CANCEL", QMessageBox::RejectRole);
  if (msgBox.exec() == QMessageBox::RejectRole) return;

  QString fileName = QFileDialog::getOpenFileName(this, "Choose File", "", "Csv Files (*.csv *.txt)");
  QFile file(fileName);
  if (fileName.isEmpty()) return;

  if (file.open(QIODevice::ReadOnly))
  {
    m_stateList->removeAllStates(); // On efface tout
    MMState *state1 = new MMState(this);
    m_stateList->addState(state1); // et on ajoute le state 1

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
      if (firstVal == "PAINT") // c'est une CUE
      {
        MMPaint *paint = new MMPaint(this);
        for (int i = 0; i < lineToken.size(); i++)
        {
          QString val = lineToken.at(i);
          val = val.trimmed();
          QVariant value(val);
          switch(i - 1) // on a déjà pris la 1ère pour typer la ligne
          {
          case Name: paint->setM_name(value.toString()); break;
          case PM_Id: paint->setM_id(value.toInt()); break;
          case PaintType:
            if (val == "Media") paint->setM_paintType(videoPaint);
            if (val == "Color") paint->setM_paintType(colorPaint);
            if (val == "Camera") paint->setM_paintType(cameraPaint);
            break;
          case PaintUri: paint->setM_uri(value.toString()); break;
          case Opacity: paint->setM_opacity(value.toInt()); break;
          case PaintRate: paint->setM_rate(value.toInt()); break;
          case PaintVolume: paint->setM_volume(value.toInt()); break;
          default: break;
          }
        }
        m_stateList->addPaint(paint);
      }
      else if (firstVal == "MAPPING")
      {
        MMMapping *mapping = new MMMapping(this);
        int lastPaintRow = m_stateList->getState(0)->getPaintCount() - 1;
        for (int i = 0; i < lineToken.size(); i++)
        {
          QString val = lineToken.at(i);
          val = val.trimmed();
          QVariant value(val);
          switch(i - 1) // on a déjà pris la 1ère pour typer la ligne
          {
          case Name: mapping->setM_name(val); break;
          case PM_Id: mapping->setM_id(value.toInt()); break;
          case Opacity: mapping->setM_opacity(value.toInt()); break;
          case MappingVisible: mapping->setVisible(value.toBool()); break;
          case MappingSolo: mapping->setSolo(value.toBool()); break;
          case MappingLocked: mapping->setLocked(value.toBool()); break;
          case MappingDepth: mapping->setM_depth(value.toInt()); break;
          default: break;
          }
        }
        m_stateList->addMapping(mapping, 0, lastPaintRow);
      }
    }
    lineindex++;
  }
  file.close();
//  hideShowColumns();
}

void TabMMState::createToolBar()
{
  layoutBar = new QHBoxLayout();

  typeBox = new QComboBox(this);
    typeBox->addItem("Paint");
    typeBox->addItem("Mapping");
    typeBox->setCurrentIndex(0);
  idLabel = new QLabel("Id", this);
  idBox = new QSpinBox(this);
    idBox->setMinimum(1);
  nameLine = new QLineEdit("paint", this);
  paintTypeBox = new QComboBox(this);
    paintTypeBox->addItem("Media");
    paintTypeBox->addItem("Color");
    paintTypeBox->addItem("Camera");
    paintTypeBox->setCurrentIndex(0);
  uriLabel = new QLabel("Choose->", this);
  uriButton = new QPushButton("File", this);
  colorLabel = new QLabel("Choose->", this);
  colorButton = new QPushButton("Color", this);
  cameraLabel = new QLabel("Choose->", this);
  cameraButton = new QPushButton("Camera", this);
  opacityLabel = new QLabel("opacity", this);
  opacityBox = new QSpinBox(this);
    opacityBox->setMinimum(0);
    opacityBox->setMaximum(100);
  rateLabel = new QLabel("rate", this);
  rateBox = new QSpinBox(this);
    rateBox->setMaximum(1000);
    rateBox->setMinimum(-1000);
  volumeLabel = new QLabel("volume", this);
  volumeBox = new QSpinBox(this);
    volumeBox->setMaximum(100);
    volumeBox->setMinimum(0);
  visibleBox = new QCheckBox("Visible", this);
  soloBox = new QCheckBox("Solo", this);
  lockBox = new QCheckBox("Locked", this);
  depthLabel = new QLabel("depth", this);
  depthBox = new QSpinBox(this);
    depthBox->setMinimum(1);
  addToStateButton = new QPushButton("Add to State", this);
    addToStateButton->setToolTip("Add to Initial Sate");
    addToStateButton->setToolTipDuration(2000);
  saveState1Button = new QPushButton("Save State1", this);
    saveState1Button->setToolTip("Save State 1 to File");
    saveState1Button->setToolTipDuration(2000);
  loadState1Button = new QPushButton("Load State1", this);
    loadState1Button->setToolTip("Load State 1 From File");
    loadState1Button->setToolTipDuration(2000);

  layoutBar->addWidget(typeBox);
  layoutBar->addWidget(idLabel);
  layoutBar->addWidget(idBox);
  layoutBar->addWidget(nameLine);
  layoutBar->addWidget(paintTypeBox);
  layoutBar->addWidget(uriLabel);
  layoutBar->addWidget(uriButton);
  layoutBar->addWidget(colorLabel);
  layoutBar->addWidget(colorButton);
  layoutBar->addWidget(cameraLabel);
  layoutBar->addWidget(cameraButton);
  layoutBar->addWidget(opacityLabel);
  layoutBar->addWidget(opacityBox);
  layoutBar->addWidget(rateLabel);
  layoutBar->addWidget(rateBox);
  layoutBar->addWidget(volumeLabel);
  layoutBar->addWidget(volumeBox);
  layoutBar->addWidget(visibleBox);
  layoutBar->addWidget(soloBox);
  layoutBar->addWidget(lockBox);
  layoutBar->addWidget(depthLabel);
  layoutBar->addWidget(depthBox);
  layoutBar->addStretch();
  layoutBar->addWidget(addToStateButton);
  layoutBar->addWidget(saveState1Button);
  layoutBar->addWidget(loadState1Button);

  connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(typeSelected(int)));
  connect(paintTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(paintTypeSelected(int)));
  connect(addToStateButton, SIGNAL(clicked()), this, SLOT(addToState()));
  connect(uriButton, SIGNAL(clicked()), this, SLOT(setUriLabel()));
  connect(colorButton, SIGNAL(clicked()), this, SLOT(setColorLabel()));
  connect(cameraButton, SIGNAL(clicked()), this, SLOT(setCameraLabel()));
  connect(saveState1Button, SIGNAL(clicked()), this, SLOT(saveAs()));
  connect(loadState1Button, SIGNAL(clicked()), this, SLOT(loadFile()));
}


