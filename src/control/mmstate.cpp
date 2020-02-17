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

#include "mmstate.h"

MMState::MMState(QObject *parent) : QObject(parent)
{

}

MMState::MMState(const MMState &mmState, QObject *parent) : QObject(parent)
{
  // Copier chaque paint et mapping
  if (v_listPaint.size())
  {
    for (int i = 0; i < v_listPaint.size(); i++)
    {
      MMPaint *tempPaint = mmState.v_listPaint.at(i);
      MMPaint *newPaint = new MMPaint(*tempPaint, this);
      v_listPaint.append(newPaint);
    }
  }
  if (v_listMapping.size())
  {
    for (int i = 0; i < v_listMapping.size(); i++)
    {
      MMMapping *tempMapping = mmState.v_listMapping.at(i);
      MMMapping *newMapping = new MMMapping(*tempMapping, this);
      v_listMapping.append(newMapping);
    }
  }
}

MMState::~MMState()
{
  qDeleteAll(v_listPaint);
  qDeleteAll(v_listMapping);
}

MMPaint *MMState::getPaint(const int vectorAt) const
{
  if (vectorAt < 0 || vectorAt >= v_listPaint.size())
  {
    qDebug() << "error getting MMPaint";
    return nullptr;
  }
  return v_listPaint.at(vectorAt);
}

MMMapping *MMState::getMapping(const int vectorAt) const
{
  if (vectorAt < 0 || vectorAt >= v_listMapping.size())
  {
    qDebug() << "error getting MMMapping";
    return nullptr;
  }
  return v_listMapping.at(vectorAt);
}

void MMState::addPaint(MMPaint *paint)
{
  paint->setParent(this);
  v_listPaint.append(paint);
}

void MMState::removePaint(const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listPaint.size()) return;
  v_listPaint.remove(vectorAt);
}

void MMState::addMapping(MMMapping *mapping)
{
  mapping->setParent(this);
  v_listMapping.append(mapping);
}

void MMState::removeMapping(const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listMapping.size()) return;
  v_listMapping.remove(vectorAt);

}
