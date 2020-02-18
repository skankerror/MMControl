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

#ifndef TABMMSTATE_H
#define TABMMSTATE_H

#include <QtWidgets>
#include "mmstatelist.h"

class TabMMState : public QWidget
{
  Q_OBJECT

public:
  explicit TabMMState(QWidget *parent = nullptr);

signals:

public slots:

private:
  MMStateList *m_mmstateList;
  QTreeView *treeView;

  QHBoxLayout *layoutMain;
    QHBoxLayout *layout1;
      QVBoxLayout *boutonLayout;
        QPushButton *boutonRemove;
        QPushButton *boutonAdd;
        QPushButton *boutonSaveAs;
        QPushButton *boutonLoad;

};

#endif // TABMMSTATE_H
