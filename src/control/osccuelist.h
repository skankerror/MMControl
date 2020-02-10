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

//#include <QObject>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include "oscsend.h"
//#include "osccue.h"
#include "osccuelistdelegate.h"
#include "MMC.h"

class OscCueList :
    public QAbstractItemModel
{
  Q_OBJECT
  Q_ENUM(columns)

public:

  explicit OscCueList(QObject *parent = nullptr);
  ~OscCueList();

// Tous les override
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  // new overrides pour tree
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
//  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
//  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

  OscSend* retOscsendFromFileLine(QStringList &lineToken); // revoir en xml ?

  OscSend* getRootSend(){ return rootSend; }; // pour tester

signals:

public /*slots*/:
  //send
//  bool addSend(OscSend *oscsend, int position, const QModelIndex &parent);
  void addCue();
  void addSend(OscSend *oscsend, int cueId);
//  void insertSend(OscSend *oscsend, int rowSend);
//  void moveSendPrev(int rowSend);
//  void moveSendNext(int rowSend);
//  void removeSend(int rowSend);
//  void removeAllSend(int cueRow);

private:
//  QVector<OscCue *> v_listCue;
  OscSend *getSend(const QModelIndex &index) const;

  OscSend *rootSend;

};

//*****************************************************************************

class OscCueListProxy :
    public QSortFilterProxyModel
{
  Q_OBJECT

public:

  explicit OscCueListProxy(OscCueList *osccuelist, QObject *parent = nullptr);
  ~OscCueListProxy(){}

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
  OscCueList * m_oscCueList;

};

#endif // OSCCUELIST_H
