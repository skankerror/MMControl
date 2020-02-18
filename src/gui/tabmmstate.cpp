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

TabMMState::TabMMState(QWidget *parent) :
  QWidget(parent)
{
  m_mmstateList = new MMStateList(this);
  treeView = new QTreeView(this);

  layoutMain = new QVBoxLayout();

  createToolBar();
  paintSelected();

  treeView->setModel(m_mmstateList);
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
  if (index == 0) paintSelected();
  if (index == 1) mappingSelected();
  return;
}

void TabMMState::paintSelected()
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

void TabMMState::mappingSelected()
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

    connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(typeSelected(int)));
    connect(paintTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(paintTypeSelected(int)));
}


