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

#ifndef OSCCUELISTDELEGATE_H
#define OSCCUELISTDELEGATE_H

#include <QtWidgets>
#include "oscsend.h"
#include "MMC.h"

class OscCuelistDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit OscCuelistDelegate(QObject *parent = nullptr);
  ~OscCuelistDelegate(){}

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//  void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const override;
//  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:

};

#endif // OSCCUELISTDELEGATE_H
