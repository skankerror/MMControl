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
{}

MMState::MMState(const MMState &mmState, QObject *parent) : QObject(parent)
{
  // Copier chaque paint
  if (v_listPaint.size())
  {
    for (int i = 0; i < v_listPaint.size(); i++)
    {
      MMPaint *tempPaint = mmState.v_listPaint.at(i);
      MMPaint *newPaint = new MMPaint(*tempPaint, this);
      v_listPaint.append(newPaint);
    }
  }
}

MMState::~MMState()
{
  qDeleteAll(v_listPaint);
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

int MMState::getPaintVectorAt(MMPaint *paint) const
{
  return v_listPaint.indexOf(paint);
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
