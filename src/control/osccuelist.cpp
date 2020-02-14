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

#include "osccuelist.h"

OscCueList::OscCueList(QObject *parent):
  QAbstractItemModel(parent)
{
  rootSend = new OscSend(this, CUE, nullptr); // on crée le rootItem
}

OscCueList::~OscCueList()
{
  delete rootSend;
}

int OscCueList::rowCount(const QModelIndex &parent) const
{
  const OscSend *parentSend = getSend(parent);
  return parentSend ? parentSend->getSendCount() : 0;
}

int OscCueList::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return Count;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }
  OscSend *tempSend = getSend(index);
  int col = index.column();
  QBrush salmonColor(QColor(SALMONCOLOR));
  QBrush yellowColor(QColor(YELLOWCOLOR));

  if (index.flags().testFlag(Qt::ItemIsEditable))
  {
    switch (role)
    {
    case Qt::DisplayRole: case Qt::EditRole:
      switch (col)
      {
      case Champ: return OscSend::getChampToString(tempSend->getChamp());
        break;
      case P_name: return tempSend->getP_name(); break;
      case P_name2: return tempSend->getP_name2(); break;
      case Uri: return tempSend->getP_uri(); break;
      case Color: return tempSend->getP_color(); break;
      case P_Id: return tempSend->getP_ID1(); break;
      case P_Id2: return tempSend->getP_ID2(); break;
      case Rate: return tempSend->getP_rate(); break;
      case P_opac: return tempSend->getP_opacity(); break;
      case Vol: return tempSend->getP_volume(); break;
      case M_name: return tempSend->getM_name(); break;
      case M_name2: return tempSend->getM_name2(); break;
      case M_Id: return tempSend->getM_ID1(); break;
      case M_opac: return tempSend->getM_opacity(); break;
      case Visible: return tempSend->getM_isvisible(); break;
      case Solo: return tempSend->getM_issolo(); break;
      case Lock: return tempSend->getM_islocked(); break;
      case Depth: return tempSend->getM_depth(); break;
      case Fade_In: return tempSend->getIsfadein(); break;
      case Time: return tempSend->getTime(); break;
      case Wait: return tempSend->getTimewait(); break;
      case Note: return tempSend->getNoteSend(); break;
      default: break;
      } break;
    case Qt::BackgroundRole:
      if (tempSend->getChamp() == CUE) return yellowColor;
      if(col == Champ) return salmonColor;
      switch(tempSend->getChamp())
      {
      case P_NAME: if(col == P_name || col == P_Id) return salmonColor; break;
      case P_REWIND: if(col == P_Id) return salmonColor; break;
      case P_COLOR:
        if(col == P_Id) return salmonColor;
        if(col == Color) return QColor(tempSend->getP_color());
        break;
      case P_OPACITY: if(col == P_Id || col == P_opac) return salmonColor; break;
      case P_VOLUME: if(col == P_Id || col == Vol) return salmonColor; break;
      case P_RATE: if(col == P_Id || col == Rate) return salmonColor; break;
      case P_URI: if(col == Uri || col == P_Id) return salmonColor; break;
      case M_NAME: if(col == M_name || col == M_Id) return salmonColor; break;
      case M_OPACITY: if(col == M_opac || col == M_Id) return salmonColor; break;
      case M_VISIBLE: if(col == Visible || col == M_Id) return salmonColor; break;
      case M_SOLO: if(col == M_Id || col == Solo) return salmonColor; break;
      case M_LOCK: if(col == M_Id || col == Lock) return salmonColor; break;
      case M_DEPTH: if(col == M_Id || col == Depth) return salmonColor; break;
      case P_XFADE: if(col == P_Id || col == P_Id2 || col == Time) return salmonColor; break;
      case P_FADE: if(col == P_Id || col == Fade_In || col == Time) return salmonColor; break;
      case R_P_NAME: if(col == P_name || col == P_name2) return salmonColor; break;
      case R_P_REWIND: if(col == P_name) return salmonColor; break;
      case R_P_OPACITY: if(col == P_name || col == P_opac) return salmonColor; break;
      case R_P_VOLUME: if(col == P_name || col == Vol) return salmonColor; break;
      case R_P_RATE: if(col == P_name || col == Rate) return salmonColor; break;
      case R_P_URI: if(col == P_name || col == Uri) return salmonColor; break;
      case R_P_COLOR: if(col == P_name || col == Color) return salmonColor; break;
      case R_M_NAME: if(col == M_name || col == M_name2) return salmonColor; break;
      case R_M_OPACITY: if(col == M_name || col == M_opac) return salmonColor; break;
      case R_M_VISIBLE: if(col == M_name || col == Visible) return salmonColor; break;
      case R_M_SOLO: if(col == M_name || col == Solo) return salmonColor; break;
      case R_M_LOCK: if(col == M_name || col == Lock) return salmonColor; break;
      case R_M_DEPTH: if(col == M_name || col == Depth) return salmonColor; break;
      case R_P_FADE: if(col == P_name || col == Fade_In || col == Time) return salmonColor; break;
      case R_P_XFADE: if(col == P_name || col == P_name2 || col == Time) return salmonColor; break;
      default: break;
      } break;
    case Qt::TextAlignmentRole: return Qt::AlignCenter;
    default: break;
    }
  }
  else if (role == Qt::BackgroundRole && tempSend->getChamp() == CUE) return yellowColor; // pour afficher les lignes de cue en jaune
  if (index.flags().testFlag(Qt::ItemIsSelectable))
  {
    if (role == Qt::DisplayRole && col == Champ)
    {
      QString value = QString("CUE %1 - ").arg(tempSend->getSendId() + 1);
              value += tempSend->getNoteSend();
      return value; // rajouter l'ID de la cue + la note
    }
    if (role == Qt::DisplayRole && col == Wait) return tempSend->getTimewait();
    if (role == Qt::TextAlignmentRole && col == Wait) return Qt::AlignCenter;
  }
  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(role);
  if (!index.isValid() || !(index.flags().testFlag(Qt::ItemIsEditable))) return false;
  int col = index.column();
  if (isCue(index) && col == Note)
  {
    getSend(index)->setNoteSend(value.toString());
    emit dataChanged(index, index);
    return true;
  }
  OscSend *tempSend = getSend(index);
  OscSend *tempCue = tempSend->getParentSend();
  double oldTimeWait = tempSend->getTimewait();
  double oldTime = tempSend->getTime();
  double oldTotalTime = tempCue->getTimewait();

  switch(col)
  {
  case Champ: tempSend->setChamp(static_cast<champMM>(value.toInt())); break;
  case P_name: tempSend->setP_name(value.toString()); break;
  case P_name2: tempSend->setP_name2(value.toString()); break;
  case Uri: tempSend->setP_uri(value.toString()); break;
  case Color: tempSend->setP_color(value.toString()); break;
  case P_Id: tempSend->setP_ID1(value.toInt()); break;
  case P_Id2: tempSend->setP_ID2(value.toInt()); break;
  case Rate: tempSend->setP_rate(value.toInt()); break;
  case P_opac: tempSend->setP_opacity(value.toInt()); break;
  case Vol: tempSend->setP_volume(value.toInt()); break;
  case M_name: tempSend->setM_name(value.toString()); break;
  case M_name2: tempSend->setM_name2(value.toString()); break;
  case M_Id: tempSend->setM_ID1(value.toInt()); break;
  case M_opac: tempSend->setM_opacity(value.toInt()); break;
  case Visible: tempSend->setM_isvisible(value.toBool()); break;
  case Solo: tempSend->setM_issolo(value.toBool()); break;
  case Lock: tempSend->setM_islocked(value.toBool()); break;
  case Depth: tempSend->setM_depth(value.toInt()); break;
  case Fade_In: tempSend->setIsfadein(value.toBool()); break;
  case Time:
    tempSend->setTime(value.toDouble());
    tempCue->setTimewait(oldTotalTime - oldTime + value.toDouble()); // update temps
    break;
  case Wait:
   tempSend->setTimewait(value.toDouble());
   tempCue->setTimewait(oldTotalTime - oldTimeWait + value.toDouble()); //update temps
   break;
  case Note: tempSend->setNoteSend(value.toString()); break;
  default: break;
  }
  emit dataChanged(index, index);
  return true;
}

QVariant OscCueList::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      switch(section)
      {
      case Champ: return QString("Champ");
      case P_name: return QString("P_name");
      case P_name2: return QString("p_name2");
      case Uri: return QString("Uri");
      case Color: return QString("Color");
      case P_Id: return QString("P_Id");
      case P_Id2: return QString("P_Id2");
      case Rate: return QString("Rate");
      case P_opac: return QString("P_opac");
      case Vol: return QString("Vol");
      case M_name: return QString("M_name");
      case M_name2: return QString("M_name2");
      case M_Id: return QString("M_Id");
      case M_opac: return QString("M_opac");
      case Visible: return QString("Visible");
      case Solo: return QString("Solo");
      case Lock: return QString("Lock");
      case Depth: return QString("Depth");
      case Fade_In: return QString("Fade_In");
      case Time: return QString("Time");
      case Wait: return QString("Wait");
      case Note: return QString("Note");
      default: return QVariant(); break;
      }
    }
  }
  if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal) return Qt::AlignCenter;
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return Qt::NoItemFlags;
  // Il faut aussi afficher wait sauf sur les cue
  OscSend *tempSend = getSend(index);
  champMM champ = tempSend->getChamp();
  int col = index.column();
  if (col == Note) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  switch(champ)
  {
  case CUE: if (col == Champ || col == Wait) return Qt::ItemIsEnabled | Qt::ItemIsSelectable; break;
  case P_NAME: if (col == P_name || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;break;
  case P_REWIND: if (col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_COLOR: if (col == Color || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_OPACITY: if (col == P_Id || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_VOLUME: if (col == P_Id || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_RATE: if (col == P_Id || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_URI: if (col == Uri || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_NAME: if (col == M_name || col == M_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_OPACITY: if (col == M_Id || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_VISIBLE: if (col == M_Id || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_SOLO: if (col == M_Id || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_LOCK: if (col == M_Id || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case M_DEPTH: if (col == M_Id || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_XFADE: if (col == P_Id || col == P_Id2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case P_FADE: if (col == P_Id || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_NAME: if (col == P_name || col == P_name2)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_REWIND: if (col == P_name) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_OPACITY: if (col == P_name || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_VOLUME: if (col == P_name || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_RATE: if (col == P_name || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_URI: if (col == P_name || col == Uri) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_COLOR: if (col == P_name || col == Color) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_NAME: if (col == M_name || col == M_name2) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_OPACITY: if (col == M_name || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_VISIBLE: if (col == M_name || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_SOLO: if (col == M_name || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_LOCK: if (col == M_name || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_M_DEPTH: if (col ==M_name || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_FADE: if (col == P_name || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  case R_P_XFADE: if (col == P_name || col == P_name2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; break;
  default: break;
  }
  if (col == Champ || col == Wait) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  return QAbstractItemModel::flags(index);
}

QModelIndex OscCueList::index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid() && parent.column() !=0) return QModelIndex();

  OscSend *parentSend = getSend(parent);
  if (!parentSend) return QModelIndex();
  OscSend *childSend = parentSend->getChild(row);
  if (childSend) return createIndex(row, column, childSend);

  return QModelIndex();
}

QModelIndex OscCueList::parent(const QModelIndex &index) const
{
  if (!index.isValid()) return QModelIndex();

  OscSend *childSend = getSend(index);
  OscSend *parentSend = childSend ? childSend->getParentSend() : nullptr;

  if (parentSend == rootSend || !parentSend) return QModelIndex();

  return createIndex(parentSend->getSendId(), 0, parentSend);
}

OscSend* OscCueList::retOscsendFromFileLine(QStringList &lineToken)
{
  champMM m_champ = CUE;
  int m_champInt = 0;
  QString m_p_name = "";
  QString m_p_name2 = "";
  QString m_p_uri = "";
  QString m_p_color = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0;
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;
  QString m_m_name = "";
  QString m_m_name2 = "";
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  int m_m_depth = 0;
  double m_time = 0;
  bool m_isfadein = false;
  double m_timewait = false;
  QString m_noteSend = "";

  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    val = val.trimmed();
    //    qDebug() << val << ", ";
    QVariant value(val);
    switch(j)
    {
    case Champ: m_champInt = OscSend::getChampFromString(val); break;
    case P_name: m_p_name = value.toString(); break;
    case P_name2: m_p_name2 = value.toString(); break;
    case Uri: m_p_uri = value.toString(); break;
    case Color: m_p_color = value.toString(); break;
    case P_Id: m_p_ID1 = value.toInt(); break;
    case P_Id2: m_p_ID2 = value.toInt(); break;
    case Rate: m_p_rate = value.toInt(); break;
    case P_opac: m_p_opacity = value.toInt(); break;
    case Vol: m_p_volume = value.toInt(); break;
    case M_name: m_m_name = value.toString(); break;
    case M_name2: m_m_name2 = value.toString(); break;
    case M_Id: m_m_ID1 = value.toInt(); break;
    case M_opac: m_m_opacity = value.toInt(); break;
    case Visible: m_m_isvisible = value.toBool(); break;
    case Solo: m_m_issolo = value.toBool(); break;
    case Lock: m_m_islocked = value.toBool(); break;
    case Depth: m_m_depth = value.toInt(); break;
    case Fade_In: m_isfadein = value.toBool(); break;
    case Time: m_time = value.toDouble(); break;
    case Wait: m_timewait = value.toDouble(); break;
    case Note: m_noteSend = value.toString(); break;
    default: break;
    }
    m_champ = static_cast<champMM>(m_champInt);
  }
  //  qDebug()<< "champ dans l'oscsend qui retourne" << m_champ;

  auto *oscsend = new OscSend(
        this,
        m_champ,
        rootSend, // en attendant...
        m_p_uri,
        m_p_name,
        m_p_name2,
        m_p_color,
        m_p_ID1,
        m_p_ID2,
        m_p_rate,
        m_p_opacity,
        m_p_volume,
        m_m_name,
        m_m_name2,
        m_m_ID1,
        m_m_opacity,
        m_m_isvisible,
        m_m_issolo,
        m_m_islocked,
        m_m_depth,
        m_time,
        m_isfadein,
        m_timewait,
        m_noteSend
        );

  return oscsend;
}

void OscCueList::addCueFromFileLine(QStringList &lineToken)
{
  QString val = lineToken.at(21);
  val = val.trimmed();
  addCue();
  OscSend *lastCue = getSend(index(rowCount() - 1, 0, QModelIndex()));
  lastCue->setNoteSend(val);
}

void OscCueList::addCue()
{
  OscSend *osccue = new OscSend(this, CUE, rootSend); // On crée une cue
  beginInsertRows(QModelIndex(), rootSend->getSendCount(), 0);
  rootSend->insertSend(osccue, rootSend->getSendCount());
  endInsertRows();
}

void OscCueList::addSend(OscSend *oscsend, int cueId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return;
  OscSend *osccue = rootSend->getChild(cueId);
  oscsend->setParentSend(osccue);
  beginInsertRows(index(cueId, 0, QModelIndex()), osccue->getSendCount(), 0);
  osccue->insertSend(oscsend, osccue->getSendCount());
  endInsertRows();
}

void OscCueList::insertSend(OscSend *oscsend, int cueId, int sendId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return;
  OscSend *osccue = rootSend->getChild(cueId);
  if (sendId < 0 || sendId >= osccue->getSendCount()) return;
  oscsend->setParentSend(osccue);
  beginInsertRows(index(cueId, 0, QModelIndex()), sendId, sendId);
  osccue->insertSend(oscsend, sendId);
  endInsertRows();
}

bool OscCueList::moveSendPrev(int cueId, int sendId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return false;
  OscSend *osccue = rootSend->getChild(cueId);
  if (sendId < 0 || sendId >= osccue->getSendCount()) return false;
  if (sendId) // Si c'est pas le 1er send de la cue
  {
    beginMoveRows(index(cueId, 0, QModelIndex()), sendId, sendId, index(cueId, 0, QModelIndex()), sendId - 1);
    osccue->moveChildPrev(sendId);
    endMoveRows();
    return false;
  }
  // C'est le 1er send
  if (cueId == 0) return false; // y a pas de cue avant on return;
  OscSend *cuePrev = rootSend->getChild(cueId - 1); // On choppe la cue d'avant
  OscSend *oscsend = osccue->getChild(sendId); // On choppe le send
  OscSend *oscsend2 = new OscSend(oscsend); // On le copie
  oscsend2->setParent(this); // On met le bon parent QObject sinon ça plante
  oscsend2->setParentSend(cuePrev); // On met la nouvelle cue comme parentsend
  removeSend(cueId, sendId); // on peut le détruire de l'ancienne cue
  addSend(oscsend2, cueId - 1); // On ajoute la copie à la bonne cue
  return true; //Pour dire à tabseq qu'on a changé de cue
}

bool OscCueList::moveSendNext(int cueId, int sendId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return false;
  OscSend *osccue = rootSend->getChild(cueId);
  if (sendId < 0 || sendId >= osccue->getSendCount()) return false;
  // Si c'est pas le dernier send
  if (sendId != osccue->getSendCount() - 1) moveSendPrev(cueId, sendId + 1);
  // C'est le dernier send
  else
  {
    if (cueId == rootSend->getSendCount() - 1) return false; // C'est la dernière cue on return
    OscSend *cueNext = rootSend->getChild(cueId + 1); // On choppe la cue d'avant
    OscSend *oscsend = osccue->getChild(sendId); // On choppe le send
    OscSend *oscsend2 = new OscSend(oscsend); // On le copie
    oscsend2->setParent(this); // On met le bon parent QObject sinon ça plante
    oscsend2->setParentSend(cueNext); // On met la nouvelle cue comme parentsend
    if (cueNext->getSendCount()) insertSend(oscsend2, cueId + 1, 0); // On ajoute la copie à la bonne cue
    else addSend(oscsend2, cueId + 1); // Si la cue a pas encore de send
    removeSend(cueId, sendId); // on peut le détruire de l'ancienne cue
    return true; //Pour dire à tabSeq qu'on a changé de cue
  }
  return false;
}

void OscCueList::removeSend(int cueId, int sendId/*, bool destroy*/)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return;
  OscSend *osccue = rootSend->getChild(cueId);
  if (sendId < 0 || sendId >= osccue->getSendCount()) return;
  beginRemoveRows(index(cueId, 0, QModelIndex()), sendId, sendId);
  osccue->removeSends(sendId);
  endRemoveRows();
}

void OscCueList::removeAllSend(int cueId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount()) return;
  OscSend *osccue = rootSend->getChild(cueId);
  int sendCount = osccue->getSendCount();
  if (!sendCount) return;
  beginRemoveRows(index(cueId, 0, QModelIndex()), 0, sendCount);
  osccue->removeSends(0, sendCount);
  endMoveRows();
}

void OscCueList::insertCue(int cueId) // A vérifier...
{
  if (cueId < 0 || cueId >= rootSend->getSendCount())
  {
    addCue(); // On add quand même...
    return;
  }
  OscSend *osccue = new OscSend(this, CUE, rootSend); // On crée une cue
  beginInsertRows(QModelIndex(), cueId, cueId);
  rootSend->insertSend(osccue, cueId);
  endInsertRows();
}

void OscCueList::moveCuePrev(int cueId)
{
  if (cueId < 1 || cueId >= rootSend->getSendCount()) return;
  beginMoveRows(QModelIndex(), cueId, cueId, QModelIndex(), cueId - 1);
  rootSend->moveChildPrev(cueId);
  endMoveRows();
}

void OscCueList::moveCueNext(int cueId)
{
  if (cueId < 0 || cueId >= rootSend->getSendCount() - 1) return;
  moveCuePrev(cueId + 1);
}

void OscCueList::removeCue(int cueId)
{
  if (cueId >=0 && cueId < rootSend->getSendCount())
  {
    beginRemoveRows(QModelIndex(), cueId, cueId);
    rootSend->removeSends(cueId);
    endRemoveRows();
  }
}

void OscCueList::removeAllCue()
{
  int cueCount = rootSend->getSendCount();
  for (int cueId = 0; cueId < cueCount; cueId++)
    removeCue(0);
}

bool OscCueList::isCue(const QModelIndex &index) const
{
  OscSend *tempSend = getSend(index);
  if (tempSend->getChamp() == CUE) return true;
  return false;
}

bool OscCueList::hideShowColumn(int col) const
{

  for(int i = 0; i < rowCount(); i++)
  {
    for (int j = 0; j < getSend(index(i, 0))->getSendCount(); j++)
    {
      if ((index(j, col, index(i, 0))).flags().testFlag(Qt::ItemIsEditable)) return true;
    }
  }
  return false;
}


OscSend *OscCueList::getSend(const QModelIndex &index) const
{
  if (index.isValid())
  {
    OscSend *oscsend =static_cast<OscSend* >(index.internalPointer());
    if (oscsend) return oscsend;
  }
  return rootSend;
}

//*************************************************************************************

OscCuelistDelegate::OscCuelistDelegate(QObject *parent):
  QStyledItemDelegate(parent)
{}

QWidget *OscCuelistDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *champComboBox = new QComboBox(parent);
    for (int i = 0; i < CUE; i++) champComboBox->addItem(OscSend::getChampToString(i));
    return champComboBox;
  }

  if (index.column() == Color)
  {
    auto *colorDialog = new QColorDialog(parent);
    colorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
    return colorDialog;
  }

  if (index.column() == Uri)
  {
    auto *fileDialog = new QFileDialog(parent);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("Media Files (*.png *.jpg *.gif *.tif *.mov *.avi *.mp4)");
    return fileDialog;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void OscCuelistDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox)
    {
      int champInt = index.model()->data(index).toInt();
      champMM champ = static_cast<champMM>(champInt);
      const int value = champ;
      comboBox->setCurrentIndex(value);
    }
  }
  if (index.column() == Color)
  {
    auto *colorDialog = qobject_cast<QColorDialog *>(editor);
    if (editor)
    {
      QColor color = QColor(index.model()->data(index).toString());
      colorDialog->setCurrentColor(color);
    }
  }
  else
  {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void OscCuelistDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if (index.column() == Champ)
  {
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    if (editor) model->setData(index, comboBox->currentIndex());
  }

  else if (index.column() == Color)
  {
    auto *colorDialog = qobject_cast<QColorDialog *>(editor);
    if (editor) model->setData(index, colorDialog->selectedColor().name());
  }

  else if (index.column() == Uri)
  {
    auto *fileDialog = qobject_cast<QFileDialog *>(editor);
    if (editor) model->setData(index, fileDialog->selectedFiles());
  }

  else
  {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void OscCuelistDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}

