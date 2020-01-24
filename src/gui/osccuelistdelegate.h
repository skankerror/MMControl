#ifndef OSCCUELISTDELEGATE_H
#define OSCCUELISTDELEGATE_H

#include <QtWidgets>
#include <QObject>
#include <QStyledItemDelegate>
#include "MMC.h"

class OscCuelistDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit OscCuelistDelegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;

  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
  void paint ( QPainter * painter, const QStyleOptionViewItem & option,
                                    const QModelIndex & index ) const override;


signals:

};

#endif // OSCCUELISTDELEGATE_H
