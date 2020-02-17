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
#include <QDebug>
#include "mmpaint.h"
#include "mmmapping.h"

class MMState : public QObject
{
  Q_OBJECT
public:
  explicit MMState(QObject *parent = nullptr);
  MMState(const MMState &mmState, QObject *parent = nullptr);
  ~MMState();

  //getters
  MMPaint *getPaint(const int vectorAt) const;
  int getPaintCount() const { return v_listPaint.size(); }
  MMMapping *getMapping(const int vectorAt) const;
  int getMappingCount() const { return v_listMapping.size(); };

  //setters
  void addPaint(MMPaint *paint);
  void removePaint(const int vectorAt);
  void addMapping(MMMapping *mapping);
  void removeMapping(const int vectorAt);

signals:

public slots:

private:
  QVector<MMPaint *> v_listPaint;
  QVector<MMMapping *>v_listMapping;
//  bool isPlayingState = false;
};

#endif // MMSTATE_H
