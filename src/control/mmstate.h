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

#ifndef MMSTATE_H
#define MMSTATE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QColor>

class MMState : public QObject
{
  Q_OBJECT
public:
  explicit MMState(QObject *parent = nullptr);

signals:

public slots:

private:
  QVector<QString *> v_uri;
  QVector<int > v_rate;
  QVector<int> v_p_opacity;
  QVector<int> v_m_opacity;
  QVector<bool> v_isSolo;
  QVector<bool> v_isVisible;
  bool pausePlay;
  // bool isRewind;
  QVector<QColor*> v_color;
};

#endif // MMSTATE_H
