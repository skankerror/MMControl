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
    QComboBox *champComboBox = new QComboBox(parent);
    champComboBox->addItem("NOOP");
    champComboBox->addItem("PLAY");
    champComboBox->addItem("PAUSE");
    champComboBox->addItem("REWIND");
    champComboBox->addItem("QUIT");
    champComboBox->addItem("P_NAME");
    champComboBox->addItem("P_REWIND");
    champComboBox->addItem("P_OPACITY");
    champComboBox->addItem("P_VOLUME");
    champComboBox->addItem("P_RATE");
    champComboBox->addItem("P_URI");
    champComboBox->addItem("P_COLOR");
    champComboBox->addItem("M_NAME");
    champComboBox->addItem("M_OPACITY");
    champComboBox->addItem("M_VISIBLE");
    champComboBox->addItem("M_SOLO");
    champComboBox->addItem("M_LOCK");
    champComboBox->addItem("M_DEPTH");
    champComboBox->addItem("P_XFADE");
    champComboBox->addItem("P_FADE");
    champComboBox->addItem("R_P_NAME");
    champComboBox->addItem("R_P_REWIND");
    champComboBox->addItem("R_P_OPACITY");
    champComboBox->addItem("R_P_VOLUME");
    champComboBox->addItem("R_P_RATE");
    champComboBox->addItem("R_P_URI");
    champComboBox->addItem("R_P_COLOR");
    champComboBox->addItem("R_M_NAME");
    champComboBox->addItem("R_M_OPACITY");
    champComboBox->addItem("R_M_VISIBLE");
    champComboBox->addItem("R_M_SOLO");
    champComboBox->addItem("R_M_LOCK");
    champComboBox->addItem("R_M_DEPTH");
    champComboBox->addItem("R_P_FADE");
    champComboBox->addItem("R_P_XFADE");
    return champComboBox;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);

//  else if (col == P_name || col == P_name2 || col == M_name || col == M_name2 || col == Uri || col == Color)
//  {
//    QLineEdit *lineEdit = new QLineEdit(parent);
//    return lineEdit;
//  }
//  else if (col == Visible || col == Solo || col == Lock || col == Fade_In)
//  {
//    QCheckBox *checkBox = new QCheckBox(parent);
//    return checkBox;
//  }
//  else if (col == Time || col == Wait)
//  {
//    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(parent);
//    return doubleSpinBox;
//  }
//  else
//  {
//    QSpinBox *spinBox = new QSpinBox(parent);
//    return spinBox;
//  }
//  else if (col == Uri)
//  {
//    QLineEdit *lineEdit = new QLineEdit;
////    lineEdit->setText(QFileDialog::getOpenFileName(parent /* ???  pas sur de mon parent...*/, "Choose File",
////                                                      "/home/ray/boulot",
////                                                      "Media Files (*.png, *.jpg, *.tif, *.tiff, *.gif, *.mov, *.avi, *.mp4"));
//    return lineEdit;
//  }
//  else if (col == Color)
//  {
//    QLineEdit *lineEdit = new QLineEdit;
////    lineEdit->setText(QColorDialog::getColor(Qt::green, parent /* ???  pas sur de mon parent...*/, "Select Color",
////                                             QColorDialog::DontUseNativeDialog).name());
//    return lineEdit;
//  }
}

void OscCuelistDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox)
    {
      champMM champ = static_cast<champMM>(index.model()->data(index).toInt()); // ça marche pas, renvoie NOOP
      const int value = champ;
      comboBox->setCurrentIndex(value);
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
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (editor)
    {
      model->setData(index, comboBox->currentIndex());// voir à faire un cast ? il renvoie toujours 0
    }
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

void OscCuelistDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyledItemDelegate::paint(painter, option, index);
}
