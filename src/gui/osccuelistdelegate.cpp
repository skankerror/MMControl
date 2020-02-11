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

#include "osccuelistdelegate.h"

OscCuelistDelegate::OscCuelistDelegate(QObject *parent):
  QStyledItemDelegate(parent)
{}

QWidget *OscCuelistDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *champComboBox = new QComboBox(parent);
    for (int i = 0; i < Count_champMM; i++) champComboBox->addItem(OscSend::getChampToString(i));
    return champComboBox;
  }

  if (index.column() == Color)
  {
    auto *colorDialog = new QColorDialog(parent);
    colorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
    return colorDialog;
  }

  if (index.column() == Uri)
  {
    auto *fileDialog = new QFileDialog(parent);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("Media Files (*.png *.jpg *.gif *.tif *.mov *.avi *.mp4)");
    return fileDialog;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void OscCuelistDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox)
    {
      int champInt = index.model()->data(index).toInt();
      champMM champ = static_cast<champMM>(champInt);
      const int value = champ;
      comboBox->setCurrentIndex(value);
    }
  }
  if (index.column() == Color)
  {
    auto *colorDialog = qobject_cast<QColorDialog *>(editor);
    if (editor)
    {
      QColor color = QColor(index.model()->data(index).toString());
      colorDialog->setCurrentColor(color);
    }
  }
  else
  {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void OscCuelistDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    if (editor) model->setData(index, comboBox->currentIndex());
  }

  else if (index.column() == Color)
  {
    auto *colorDialog = qobject_cast<QColorDialog *>(editor);
    if (editor) model->setData(index, colorDialog->selectedColor().name());
  }

  else if (index.column() == Uri)
  {
    auto *fileDialog = qobject_cast<QFileDialog *>(editor);
    if (editor) model->setData(index, fileDialog->selectedFiles());
  }

  else
  {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void OscCuelistDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}

//void OscCuelistDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//  QStyledItemDelegate::paint(painter, option, index);
//}

//QSize OscCuelistDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//  return QStyledItemDelegate::sizeHint(option, index);
//}
