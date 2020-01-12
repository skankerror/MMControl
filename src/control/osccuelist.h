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

#ifndef OSCCUELIST_H
#define OSCCUELIST_H

#include <QObject>
#include <QVector>
#include <QAbstractTableModel>
#include <QVariant>
#include <QBrush>
#include <QTextStream>
#include <QStringList>
#include "oscsend.h"

class OscCueList :
    public QAbstractTableModel
{
  Q_OBJECT
public:
  OscCueList(QObject *parent);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  OscSend* retOscsendFromFileLine(QStringList &lineToken);

  QVector<OscSend *> v_listCue;

signals:

public slots:
  void addCue(OscSend *oscsend);
  void insertCue(OscSend *oscsend, int row);
  void moveCuePrev(int rowCue);
  void removeCue(int rowCue);
  void removeAllCue();

private:

};

#endif // OSCCUELIST_H
