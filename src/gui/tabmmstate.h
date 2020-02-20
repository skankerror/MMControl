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

#ifndef TABMMSTATE_H
#define TABMMSTATE_H

#include <QtWidgets>
#include "mmstatelist.h"

class TabMMState : public QWidget
{
  Q_OBJECT

public:
  explicit TabMMState(MMStateList *stateList, QWidget *parent = nullptr);

signals:
  void askGenerateStates();

private slots:
  void typeSelected(const int index);
  void paintTypeSelected(const int index);
  void addToState();
  void setUriLabel();
  void setColorLabel();
  void setCameraLabel();
  void saveAs();
  void loadFile();
  void deleteRow();
  void generateStates();
  void resizeColumns();

private:
  void createToolBar();
  void createLateralButtons();

  MMStateList *m_stateList;

  QVBoxLayout *layoutMain;
    QHBoxLayout *layoutBar;
      QComboBox *typeBox;
      QLabel *idLabel;
      QSpinBox *idBox;
      QLineEdit *nameLine;
      QComboBox *paintTypeBox;
      QLabel *uriLabel;
      QPushButton *uriButton;
      QLabel *colorLabel;
      QPushButton * colorButton;
      QLabel *cameraLabel;
      QPushButton *cameraButton;
      QLabel *opacityLabel;
      QSpinBox *opacityBox;
      QLabel *rateLabel;
      QSpinBox *rateBox;
      QLabel *volumeLabel;
      QSpinBox *volumeBox;
      QCheckBox *visibleBox;
      QCheckBox *soloBox;
      QCheckBox *lockBox;
      QLabel *depthLabel;
      QSpinBox *depthBox;
      QPushButton *addToStateButton;
    QHBoxLayout *layoutButtonsTree;
      QTreeView *treeView;
      QVBoxLayout *layoutButton;
        QPushButton *deleteButton;
        QPushButton *saveState1Button;
        QPushButton *loadState1Button;
        QPushButton *generateStatesButton;

};

#endif // TABMMSTATE_H
