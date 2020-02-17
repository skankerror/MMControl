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

#include "mmpaint.h"

MMPaint::MMPaint(QObject *parent) : QObject(parent)
{

}

MMPaint::MMPaint(const MMPaint &mmpaint, QObject *parent) : QObject(parent)
{
  m_id = mmpaint.m_id;
  m_name = mmpaint.m_name;
  m_paintType = mmpaint.m_paintType;
  m_uri = mmpaint.m_uri;
  m_color = mmpaint.m_color;
  m_opacity = mmpaint.m_opacity;
  m_rate = mmpaint.m_rate;
  m_volume = mmpaint.m_volume;
  v_listMappingId = mmpaint.v_listMappingId;
}

int MMPaint::getMappingId(const int vectorAt) const
{
  if (vectorAt < 0 || vectorAt >= v_listMappingId.size()) return -1;
  return v_listMappingId.at(vectorAt);
}

void MMPaint::setM_paintType(const paintType type)
{
  if (type < colorPaint || type > cameraPaint) return;
  m_paintType = type;
}

void MMPaint::addMappingId(int id)
{
  if (id) v_listMappingId.append(id);
}

void MMPaint::changeMappingId(const int id, const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listMappingId.size()) return;
  v_listMappingId[vectorAt] = id;
}

void MMPaint::removeMappingId(const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listMappingId.size()) return;
  v_listMappingId.remove(vectorAt);
}
