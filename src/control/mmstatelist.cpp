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

#include "mmstatelist.h"

MMStateList::MMStateList(QObject *parent):
  QAbstractItemModel(parent)
{
  rootState = new MMState(this); // on crée le rootItem

  // test
  MMState *state1 = new MMState(this);
//  MMPaint *paint1 = new MMPaint(state1);
//  paint1->setM_id(1);
//  paint1->setM_name("source1");
//  MMMapping *mapping1 = new MMMapping(paint1);
//  mapping1->setM_id(3);
//  mapping1->setM_name("layer3");
//  mapping1->setM_depth(3);
  addState(state1);
//  addPaint(paint1, 0);
//  addMapping(mapping1, 0, 0);
//  MMState *state2 = new MMState(*state1, this);
//  addState(state2);
}

MMStateList::~MMStateList()
{
  qDeleteAll(v_listMMState);
  delete rootState;
}

int MMStateList::rowCount(const QModelIndex &parent) const
{
  QObject *item = getItem(parent);
  if (item == rootState) return v_listMMState.size();
  QString tempString = item->metaObject()->className();
  if (tempString == "MMState")
  {
    MMState *mmState = qobject_cast<MMState *>(item);
    return mmState->getPaintCount();
  }
  if (tempString == "MMPaint")
  {
    MMPaint *mmState = qobject_cast<MMPaint *>(item);
    return mmState->getMappingCount();
  }
  return 0;
}

int MMStateList::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return columnStateCount;
}

QVariant MMStateList::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();
  QObject *item = getItem(index);
  int row = index.row();
  int col = index.column();
  QString className = item->metaObject()->className();
  if (className == "MMState" && (role == Qt::DisplayRole || role == Qt::EditRole) && col == Name)
  {
    return QString("State %1 ").arg(row + 1);
  }
  if (className == "MMPaint" && (role == Qt::DisplayRole || role == Qt::EditRole))
  {
    MMPaint *paint = qobject_cast<MMPaint *>(item);
    switch (col)
    {
    case Name: return paint->getM_name(); break;
    case PM_Id: return paint->getM_id(); break;
    case PaintType:
    {
      switch (paint->getM_paintType()) // A éditer dans le delegate
      {
      case colorPaint: return QString("Color"); break;
      case videoPaint: return QString("Media"); break;
      case cameraPaint: return QString("Camera"); break;
      default: break;
      }
      break;
    }
    case PaintUri: return paint->getM_uri(); // A détailler... delegate...
    case Opacity: return paint->getM_opacity();
    case PaintRate: return paint->getM_rate();
    case PaintVolume: return paint->getM_volume();
    default: break;
    }
  }
  if (className == "MMMapping" && (role == Qt::DisplayRole || role == Qt::EditRole))
  {
    MMMapping *mapping = qobject_cast<MMMapping *>(item);
    switch (col)
    {
    case Name: return mapping->getM_name(); break;
    case PM_Id: return mapping->getM_id(); break;
    case Opacity: return mapping->getM_opacity(); break;
    case MappingVisible: return (int)mapping->visible(); break;
    case MappingSolo: return (int)mapping->solo(); break;
    case MappingLocked: return (int)mapping->locked(); break;
    case MappingDepth: return mapping->getM_depth(); break;
    default: break;
    }
  }
  if (role == Qt::TextAlignmentRole) return Qt::AlignCenter;
  if (role == Qt::BackgroundRole)
  {
    if (className == "MMState") return yellowColor;
    if (className == "MMPaint") return blueColor;
    if (className == "MMMapping") return lighterGray;
  }
  return QVariant();
}

bool MMStateList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(index)
  Q_UNUSED(value)
  Q_UNUSED(role)
  return false;
}

QVariant MMStateList::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      switch(section)
      {
      case Name: return QString("Name");
      case PM_Id: return QString("Id");
      case PaintType: return QString("Paint Type");
      case PaintUri: return QString("Uri/Color/Caméra");
      case Opacity: return QString("Opacity");
      case PaintRate: return QString("Rate");
      case PaintVolume: return QString("Volume");
      case MappingVisible: return QString("Visible");
      case MappingSolo: return QString("Solo");
      case MappingLocked: return QString("Locked");
      case MappingDepth: return QString("Depth");
      default: return QVariant(); break;
      }
    }
  }
  if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal) return Qt::AlignCenter;
  return QVariant();
}

Qt::ItemFlags MMStateList::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return Qt::NoItemFlags;
  int col = index.column();
  QObject *item = getItem(index);
  QString className = item->metaObject()->className();
  if (className == "MMState" && col == Name)
    return index.row() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::ItemIsEnabled;
  if (className == "MMPaint")
  {
    if (col == Name || col == PM_Id || col == PaintType || col == PaintUri || col == Opacity
        || col == PaintRate || col == PaintVolume)
      // Si c'est le 1er state retourner aussi editable
      return parent(index).row() ? Qt::ItemIsEnabled
                                 : Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  if (className == "MMMapping") // rajouter Qt::ItemHasNoChildren ?
  {
    if (col == Name || col == PM_Id || col == Opacity || col == MappingVisible || col == MappingSolo
        || col == MappingLocked || col == MappingDepth)
      // Si c'est le 1er state retourner aussi editable
      return parent(parent(index)).row() ? Qt::ItemIsEnabled
                                 : Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  return Qt::NoItemFlags;
}

QModelIndex MMStateList::index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid() && parent.column() !=0) return QModelIndex(); // != 0 permet de ne sélectionner que la ligne
  QObject *parentItem = getItem(parent);
  if (!parentItem) return QModelIndex();
  if (parentItem == rootState && row >=0 && row < v_listMMState.size())
    return createIndex(row, column, v_listMMState.at(row));
  // Faire les cast
  QString classParentName = parentItem->metaObject()->className();
  if (classParentName == "MMState")
  {
    MMState *stateParent = qobject_cast<MMState *>(parentItem);
    if (row < 0 || row >= stateParent->getPaintCount()) return QModelIndex();
    return createIndex(row, column, stateParent->getPaint(row));
  }
  if (classParentName == "MMPaint")
  {
    MMPaint *paintParent = qobject_cast<MMPaint *>(parentItem);
    if (row < 0 || row >= paintParent->getMappingCount()) return QModelIndex();
    return createIndex(row, column, paintParent->getMapping(row));
  }
  return QModelIndex();
}

QModelIndex MMStateList::parent(const QModelIndex &index) const
{
  if (!index.isValid()) return QModelIndex();
  QObject *item = getItem(index);
  QObject *parentItem = item ? getParentItem(index) : nullptr;
  if (parentItem == rootState || !parentItem) return QModelIndex();
  QString classParentName = parentItem->metaObject()->className();
  int rowParent = 0;
  if (classParentName == "MMState")
  {
    MMState *stateParent = qobject_cast<MMState *>(parentItem);
    rowParent = v_listMMState.indexOf(stateParent);
    return createIndex(rowParent, 0, stateParent);
  }
  if (classParentName == "MMPaint")
  {
    MMPaint *paintParent = qobject_cast<MMPaint *>(parentItem);
    // Ils sont passés par MMState::addPaint ils ont le state pour parent
    MMState *stateGrandParent = qobject_cast<MMState *>(paintParent->parent());
    rowParent = stateGrandParent->getPaintVectorAt(paintParent);
    return createIndex(rowParent, 0, paintParent);
  }
  return QModelIndex();
}

QObject *MMStateList::getItem(const QModelIndex &index) const
{
  if (index.isValid())
  {
    QObject *item = static_cast<QObject* >(index.internalPointer());
    if (item) return item;
  }
  return rootState;
}

QObject *MMStateList::getParentItem(const QModelIndex &index) const
{
  QObject *item = getItem(index);
  QString tempString = item->metaObject()->className();
  if (tempString == "MMState")
  {
    MMState *parentItem = rootState;
    return parentItem;
  }
  else if (tempString == "MMPaint")
  {
    MMState *parentItem = qobject_cast<MMState *>(item->parent());
    return parentItem;
  }
  else if (tempString == "MMMapping")
  {
    MMPaint *parentItem = qobject_cast<MMPaint *>(item->parent());
    return parentItem;
  }
  else
  {
    QObject *parentItem = nullptr;
    return parentItem;
  }
}

MMState *MMStateList::getState(const int stateId)
{
  if (stateId < 0 || stateId >= v_listMMState.size())
  {
    qDebug() << "Problem getting MMState";
    return nullptr;
  }
  return v_listMMState.at(stateId);
}

void MMStateList::addState(MMState *state)
{
  beginInsertRows(QModelIndex(), v_listMMState.size() - 1, v_listMMState.size() - 1);
  state->setParent(rootState);
  v_listMMState.append(state);
  endInsertRows();
}

void MMStateList::insertState(MMState *state, const int stateId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  beginInsertRows(QModelIndex(), stateId, stateId);
  v_listMMState.insert(stateId, state);
  endInsertRows();
}

void MMStateList::removeState(const int stateId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  MMState *state = v_listMMState.at(stateId);
  for (int i = 0; i < state->getPaintCount(); i++)
  {
    state->removePaint(i);
  }
  beginRemoveRows(QModelIndex(), stateId, stateId);
  v_listMMState.remove(stateId);
  endRemoveRows();
}

void MMStateList::addPaint(MMPaint *paint, const int stateId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  MMState *state = v_listMMState.at(stateId);
  QModelIndex stateIndex = index(stateId, 0, QModelIndex());
  beginInsertRows(stateIndex, state->getPaintCount() - 1, state->getPaintCount() - 1);
  state->addPaint(paint);
  endInsertRows();
}

//void MMStateList::insertPaint(MMPaint *paint, const int stateId, const int paintId)
//{
//  if (stateId < 0 || stateId >= v_listMMState.size()) return;
//  MMState *state = v_listMMState.at(stateId);
//  if (paintId < 0 || paintId >= state->getPaintCount()) return;
//  QModelIndex stateIndex = index(stateId, 0, QModelIndex());
//  beginInsertRows(stateIndex, paintId, paintId);
//  state->;
//  endInsertRows();
//}

void MMStateList::removePaint(const int stateId, const int paintId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  MMState *state = v_listMMState.at(stateId);
  if (paintId < 0 || paintId >= state->getPaintCount()) return;
  MMPaint *paint = state->getPaint(paintId); // on remove ses mappings
  for (int i = 0; i < paint->getMappingCount(); i++)
  {
    paint->removeMapping(i);
  }
  QModelIndex stateIndex = index(stateId, 0, QModelIndex());
  beginRemoveRows(stateIndex, paintId, paintId);
  state->removePaint(paintId);
  endRemoveRows();
}

void MMStateList::addMapping(MMMapping *mapping, const int stateId, const int paintId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  MMState *state = v_listMMState.at(stateId);
  if (paintId <0 || paintId >= state->getPaintCount()) return;
  MMPaint *paint = state->getPaint(paintId);
  QModelIndex stateIndex = index(stateId, 0, QModelIndex());
  QModelIndex paintIndex = index(paintId, 0, stateIndex);
  beginInsertRows(paintIndex, paint->getMappingCount() - 1, paint->getMappingCount() - 1);
  paint->addMapping(mapping);
  endInsertRows();
}

void MMStateList::removeMapping(const int stateId, const int paintId, const int mappingId)
{
  if (stateId < 0 || stateId >= v_listMMState.size()) return;
  MMState *state = v_listMMState.at(stateId);
  if (paintId <0 || paintId >= state->getPaintCount()) return;
  MMPaint *paint = state->getPaint(paintId);
  if (mappingId < 0 || mappingId >= paint->getMappingCount()) return;
  QModelIndex stateIndex = index(stateId, 0, QModelIndex());
  QModelIndex paintIndex = index(paintId, 0, stateIndex);
  beginRemoveRows(paintIndex, mappingId, mappingId);
  paint->removeMapping(mappingId);
  endRemoveRows();
}

//void MMStateList::insertMapping(MMMapping *mapping, const int stateId, const int paintId, const int mappingId)
//{

//}

void MMStateList::removeAllStates() // A vérifier
{
  if (!v_listMMState.size()) return;
  beginRemoveRows(QModelIndex(), 0, v_listMMState.size() - 1);
  for (int i = 0; i < v_listMMState.size(); i++)
    removeState(0);
  endRemoveRows();
}

