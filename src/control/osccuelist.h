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
#include <QModelIndex>
#include <QAbstractTableModel>
#include <QVariant>
#include <QBrush>
#include <QTextStream>
#include <QStringList>
#include "oscsend.h"
#include "osccue.h"
#include "osccuelistdelegate.h"
#include "MMC.h"

class OscCueList :
    public QAbstractTableModel
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
// insertRows ?

  OscCue *getOscCue(const int row) const;
  int getOscCueCount() const { return v_listCue.size(); };
  bool isRowCue(const int row) const;
  int getCueId(const int row) const;
  int getSendId(const int row) const;
  int getSendCueId(const int row) const;

  // faire fonction pour avoir le row à partir de l'id de la cue

  OscSend* retOscsendFromFileLine(QStringList &lineToken); // revoir en xml ?

signals:

public slots:
  // cue
  void addCue(OscCue *osccue);
  void insertCue(OscCue *osccue, int row);
  void moveCuePrev(int rowCue);
  void removeCue(int rowCue);
  void removeAllCue();

  //send
  void addSend(OscSend *oscsend, int rowCue);
  void insertSend(OscSend *oscsend, int rowSend);
  void moveSendPrev(int rowSend);
  void removeSend(int rowSend);
  void removeAllSend(int cueRow);

private:
  QVector<OscCue *> v_listCue;

};

#endif // OSCCUELIST_H
