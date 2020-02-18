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

  layoutMain = new QHBoxLayout();
  layout1 = new QHBoxLayout();
  boutonLayout = new QVBoxLayout();

  boutonRemove = new QPushButton(this);
  QIcon binIcon = QIcon(":/graphics/Bin");
  boutonRemove->setIcon(binIcon);
  boutonRemove->setFixedSize(70, 30);
  boutonRemove->setIconSize(QSize(40, 25));
  boutonRemove->setToolTip("Remove Paint or Mapping");
  boutonRemove->setToolTipDuration(2000);

  boutonAdd = new QPushButton(this);
  QIcon plusIcon = QIcon(":/graphics/Plus");
  boutonAdd->setIcon(plusIcon);
  boutonAdd->setFixedSize(70, 30);
  boutonAdd->setIconSize(QSize(40, 25));
  boutonAdd->setToolTip("Add Paint or Mapping");
  boutonAdd->setToolTipDuration(2000);

  boutonSaveAs = new QPushButton(this);
  QIcon saveIcon = QIcon(":/graphics/Save");
  boutonSaveAs->setIcon(saveIcon);
  boutonSaveAs->setFixedSize(70, 30);
  boutonSaveAs->setIconSize(QSize(40, 25));
//  boutonSaveAs->setShortcut(QKeySequence("Ctrl+S"));
  boutonSaveAs->setToolTip("Save as\nCtrl+s");
  boutonSaveAs->setToolTipDuration(2000);

  boutonLoad = new QPushButton(this);
  QIcon loadIcon = QIcon(":/graphics/Load");
  boutonLoad->setIcon(loadIcon);
  boutonLoad->setFixedSize(70, 30);
  boutonLoad->setIconSize(QSize(40, 25));
//  boutonLoad->setShortcut(QKeySequence("Ctrl+O"));
  boutonLoad->setToolTip("Load File\nCtrl+o");
  boutonLoad->setToolTipDuration(2000);

  boutonLayout->addWidget(boutonRemove);
  boutonLayout->addWidget(boutonAdd);
  boutonLayout->addWidget(boutonSaveAs);
  boutonLayout->addWidget(boutonLoad);

  treeView->setModel(m_mmstateList);
  treeView->setTextElideMode(Qt::ElideLeft);
  treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

  treeView->show();

  layout1->addWidget(treeView);
  layoutMain->addLayout(boutonLayout);
  layoutMain->addLayout(layout1);
  this->setLayout(layoutMain);

  setAutoFillBackground(true);

}
