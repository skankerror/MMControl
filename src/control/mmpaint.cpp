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
{}

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
  // Copier chaque Mapping
  if (v_listMapping.size())
  {
    for (int i = 0; i < v_listMapping.size(); i++)
    {
      MMMapping *tempMapping = mmpaint.v_listMapping.at(i);
      MMMapping *newMapping = new MMMapping(*tempMapping, this);
      v_listMapping.append(newMapping);
    }
  }
}

MMPaint::~MMPaint()
{
  qDeleteAll(v_listMapping);
}

MMMapping *MMPaint::getMapping(const int vectorAt) const
{
  if (vectorAt < 0 || vectorAt >= v_listMapping.size())
  {
    qDebug () << "problem return MMMapping";
    return nullptr;
  }
  return v_listMapping.at(vectorAt);
}

void MMPaint::setM_paintType(const paintType type)
{
  if (type < colorPaint || type > cameraPaint) return;
  m_paintType = type;
}

void MMPaint::addMapping(MMMapping *mapping)
{
  mapping->setParent(this);
  mapping->setm_paintLinkedId(m_id);
  v_listMapping.append(mapping);
}

void MMPaint::insertMapping(MMMapping *mapping, const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listMapping.size()) return;
  mapping->setParent(this);
  mapping->setm_paintLinkedId(m_id);
  v_listMapping.insert(vectorAt, mapping);
}

void MMPaint::removeMapping(const int vectorAt)
{
  if (vectorAt < 0 || vectorAt >= v_listMapping.size()) return;
  v_listMapping.remove(vectorAt);
}
