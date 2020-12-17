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

#ifndef MMSTATELIST_H
#define MMSTATELIST_H

#include <QAbstractItemModel>
#include <QBrush>
#include "mmstate.h"

class MMStateList : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit MMStateList(QObject *parent = nullptr);
  ~MMStateList();

  // Tous les override
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  QObject *getItem(const QModelIndex &index) const; // à caster
  QObject *getParentItem(const QModelIndex &index) const; // à caster

  MMState* getState(const int stateId);
  void addState(MMState *state);
  void insertState(MMState *state, const int stateId);
  void removeState(const int stateId);
  void addPaint(MMPaint *paint, const int stateId = 0);
//  void insertPaint(MMPaint *paint, const int stateId, const int paintId);
  void removePaint(const int stateId, const int paintId);
  void addMapping(MMMapping *mapping, const int stateId, const int paintId); // Inverser pour mettre stateId = 0
//  void insertMapping(MMMapping *mapping, const int stateId, const int paintId, const int mappingId);
  void removeMapping(const int stateId, const int paintId, const int mappingId); // Inverser
  void removeAllStates();

private:
  QVector<MMState *>v_listMMState;
  MMState *rootState;

  const QBrush yellowColor = (QColor(YELLOWCOLOR));
  const QBrush blueColor = (QColor(BLUECOLOR));
  const QBrush lighterGray = (QColor(LIGHTERGRAY));

};

#endif // MMSTATELIST_H
