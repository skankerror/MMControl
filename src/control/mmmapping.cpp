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

#include "mmmapping.h"

MMMapping::MMMapping(QObject *parent) : QObject(parent)
{

}

MMMapping::MMMapping(const MMMapping &mmmapping, QObject *parent) : QObject(parent)
{
  m_id = mmmapping.m_id;
  m_name = mmmapping.m_name;
  m_paintLinkedId = mmmapping.m_paintLinkedId;
  m_opacity = mmmapping.m_opacity;
  isVisible = mmmapping.isVisible;
  isLocked = mmmapping.isLocked;
  isSolo = mmmapping.isSolo;
  m_depth = mmmapping.m_depth;
}
