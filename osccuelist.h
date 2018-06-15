#ifndef OSCCUELIST_H
#define OSCCUELIST_H

#include <QObject>
#include <QVector>
#include <QAbstractTableModel>
#include <QVariant>
#include "oscsend.h"

class OscCueList :
        public QAbstractTableModel
        //public QObject
{
    Q_OBJECT
public:
    OscCueList(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    // void editCompleted(const QString &);

public slots:
    void addCue(OscSend *oscsend);

private:
    QVector<OscSend *> v_listCue;
};

#endif // OSCCUELIST_H
