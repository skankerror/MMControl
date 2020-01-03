#ifndef OSCCUELIST_H
#define OSCCUELIST_H

#include <QObject>
#include <QVector>
#include <QAbstractTableModel>
#include <QVariant>
#include "oscsend.h"
#include <QBrush>
#include <QTextStream>
#include <QStringList>

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
  void moveCuePrev(int rowCue);
  void removeCue(int rowCue);

private:

};

#endif // OSCCUELIST_H
