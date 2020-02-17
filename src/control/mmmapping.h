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

#ifndef MMMAPPING_H
#define MMMAPPING_H

#include <QObject>

class MMMapping : public QObject
{
  Q_OBJECT

public:
  explicit MMMapping(QObject *parent = nullptr);
  MMMapping(const MMMapping &mmmapping, QObject *parent = nullptr);

  // getters
  int getM_id() const { return m_id; };
  QString getM_name() const { return m_name; };
  int getM_paintLinkedId() const { return m_paintLinkedId; };
  int getM_opacity() const { return m_opacity; };
  bool visible() const { return isVisible; };
  bool locked() const { return isLocked; };
  bool solo() const { return isSolo; };
  int getM_depth() const {return m_depth; };

  // setters
  void setM_id(const int id) { m_id = id; };
  void setM_name(const QString name) { m_name = name; };
  void setm_paintLinkedId(const int id) { m_paintLinkedId = id; };
  void setM_opacity(const int opacity) { m_opacity = opacity; };
  void setVisible(const bool visible) { isVisible = visible; };
  void setLocked(const bool locked) { isLocked = locked; };
  void setSolo(const bool solo) { isSolo = solo; };
  void setM_depth(const int depth) { m_depth = depth; };

private:
  int m_id;
  QString m_name;
  int m_paintLinkedId;
  int m_opacity;
  bool isVisible;
  bool isLocked;
  bool isSolo;
  int m_depth;
};

#endif // MMMAPPING_H
