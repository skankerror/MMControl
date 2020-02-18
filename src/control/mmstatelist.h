#ifndef MMSTATELIST_H
#define MMSTATELIST_H

#include <QAbstractItemModel>
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

  void addState(MMState *state);
  void insertState(MMState *state, const int stateId);
  void removeState(const int stateId);
  void addPaint(MMPaint *paint, const int stateId);
//  void insertPaint(MMPaint *paint, const int stateId, const int paintId);
  void removePaint(const int stateId, const int paintId);
  void addMapping(MMMapping *mapping, const int stateId, const int paintId);
//  void insertMapping(MMMapping *mapping, const int stateId, const int paintId, const int mappingId);
  void removeMapping(const int stateId, const int paintId, const int mappingId);
  void removeAllStates();

private:
  QVector<MMState *>v_listMMState;
  MMState *rootState;
};

#endif // MMSTATELIST_H
