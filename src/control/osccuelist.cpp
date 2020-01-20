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
  QAbstractTableModel(parent)
{

}

int OscCueList::rowCount(const QModelIndex &index) const
{
  return index.isValid() ? 0 : v_listCue.size();
}

int OscCueList::columnCount(const QModelIndex &index) const
{
  return index.isValid() ? 0 : Count;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const // voir pour mettre en italique les cue à enchaîner
{
  if (!index.isValid() || index.row() < 0 || index.row() >= v_listCue.size() || !(index.flags().testFlag(Qt::ItemIsEditable)))
     {
         return QVariant();
     }
  int col = index.column();
  OscSend *tempSend = v_listCue.at(index.row());
  QBrush salmonColor(QColor("#59271E"));
  switch (role)
      {
      case Qt::DisplayRole: case Qt::EditRole:
        switch (col) {
        case Champ:
          switch(tempSend->m_champ) {
          case NOOP: return QString("NOOP"); break;
          case PLAY: return QString("PLAY"); break;
          case PAUSE: return QString("PAUSE"); break;
          case REWIND: return QString("REWIND"); break;
          case QUIT: return QString("QUIT"); break;
          case P_NAME: return QString("P_NAME"); break;
          case P_REWIND: return QString("P_REWIND"); break;
          case P_OPACITY: return QString("P_OPACITY"); break;
          case P_VOLUME: return QString("P_VOLUME"); break;
          case P_RATE: return QString("P_RATE"); break;
          case P_URI: return QString("P_URI"); break;
          case P_COLOR: return QString("P_COLOR"); break;
          case M_NAME: return QString("M_NAME"); break;
          case M_OPACITY: return QString("M_OPACITY"); break;
          case M_VISIBLE: return QString("M_VISIBLE"); break;
          case M_SOLO: return QString("M_SOLO"); break;
          case M_LOCK: return QString("M_LOCK"); break;
          case M_DEPTH: return QString("M_DEPTH"); break;
          case P_XFADE: return QString("P_XFADE"); break;
          case P_FADE: return QString("P_FADE"); break;
          case R_P_NAME: return QString("R_P_NAME"); break;
          case R_P_REWIND: return QString("R_P_REWIND"); break;
          case R_P_OPACITY: return QString("R_P_OPACITY"); break;
          case R_P_VOLUME: return QString("R_P_VOLUME"); break;
          case R_P_RATE: return QString("R_P_RATE"); break;
          case R_P_URI: return QString("R_P_URI"); break;
          case R_P_COLOR: return QString("R_P_COLOR"); break;
          case R_M_NAME: return QString("R_M_NAME"); break;
          case R_M_OPACITY: return QString("R_M_OPACITY"); break;
          case R_M_VISIBLE: return QString("R_M_VISIBLE"); break;
          case R_M_SOLO: return QString("R_M_SOLO"); break;
          case R_M_LOCK: return QString("R_M_LOCK"); break;
          case R_M_DEPTH: return QString("R_M_DEPTH"); break;
          case R_P_FADE: return QString("R_P_FADE"); break;
          case R_P_XFADE: return QString("R_P_XFADE"); break;
          default: break;
          }
          break;
        case P_name: return tempSend->m_p_name; break;
        case P_name2: return tempSend->m_p_name2; break;
        case Uri: return tempSend->m_p_uri; break;
        case Color: return tempSend->m_p_color; break;
        case P_Id: return tempSend->m_p_ID1; break;
        case P_Id2: return tempSend->m_p_ID2; break;
        case Rate: return tempSend->m_p_rate; break;
        case P_opac: return tempSend->m_p_opacity; break;
        case Vol: return tempSend->m_p_volume; break;
        case M_name: return tempSend->m_m_name; break;
        case M_name2: return tempSend->m_m_name2; break;
        case M_Id: return tempSend->m_m_ID1; break;
        case M_opac: return tempSend->m_m_opacity; break;
        case Visible: return tempSend->m_m_isvisible; break;
        case Solo: return tempSend->m_m_issolo; break;
        case Lock: return tempSend->m_m_islocked; break;
        case Depth: return tempSend->m_m_depth; break;
        case Fade_In: return tempSend->m_isfadein; break;
        case Time: return tempSend->m_time; break;
        case Wait: return tempSend->m_timeWait; break;
        default: break;
        }
        break;
      }

  if (role == Qt::BackgroundRole)
  {
    if(col == 0) return salmonColor;
    switch(tempSend->m_champ){
    case P_NAME: if(col == 1 || col == 5) return salmonColor; break;
    case P_REWIND: if(col == 5) return salmonColor; break;
    case P_COLOR: if(col == 4 || col == 5) return salmonColor; break;
    case P_OPACITY: if(col == 5 || col == 8) return salmonColor; break;
    case P_VOLUME: if(col == 5 || col == 9) return salmonColor; break;
    case P_RATE: if(col == 5 || col == 7) return salmonColor; break;
    case P_URI: if(col == 3 || col == 5) return salmonColor; break;
    case M_NAME: if(col == 10 || col == 12) return salmonColor; break;
    case M_OPACITY: if(col == 12 || col == 13) return salmonColor; break;
    case M_VISIBLE: if(col == 12 || col == 14) return salmonColor; break;
    case M_SOLO: if(col == 12 || col == 15) return salmonColor; break;
    case M_LOCK: if(col == 12 || col == 16) return salmonColor; break;
    case M_DEPTH: if(col == 12 || col == 17) return salmonColor; break;
    case P_XFADE: if(col == 5 || col == 6 || col == 19) return salmonColor; break;
    case P_FADE: if(col == 5 || col == 18 || col == 19) return salmonColor; break;
    case R_P_NAME: if(col == 1 || col == 2) return salmonColor; break;
    case R_P_REWIND: if(col == 1) return salmonColor; break;
    case R_P_OPACITY: if(col == 1 || col == 8) return salmonColor; break;
    case R_P_VOLUME: if(col == 1 || col == 9) return salmonColor; break;
    case R_P_RATE: if(col == 1 || col == 7) return salmonColor; break;
    case R_P_URI: if(col == 1 || col == 3) return salmonColor; break;
    case R_P_COLOR: if(col == 1 || col == 4) return salmonColor; break;
    case R_M_NAME: if(col == 10 || col == 11) return salmonColor; break;
    case R_M_OPACITY: if(col == 10 || col == 13) return salmonColor; break;
    case R_M_VISIBLE: if(col == 10 || col == 14) return salmonColor; break;
    case R_M_SOLO: if(col == 10 || col == 15) return salmonColor; break;
    case R_M_LOCK: if(col == 10 || col == 16) return salmonColor; break;
    case R_M_DEPTH: if(col == 10 || col == 17) return salmonColor; break;
    case R_P_FADE: if(col == 1 || col == 18 || col == 19) return salmonColor; break;
    case R_P_XFADE: if(col == 1 || col == 2 || col == 19) return salmonColor; break;
    default: break;
    }
    if (tempSend->m_timeWait > 0) return QBrush(Qt::Dense4Pattern);

  }
  if (role == Qt::TextAlignmentRole) return Qt::AlignCenter;
  if (role == Qt::ForegroundRole){/* à voir*/}
  if (role == Qt::SizeHintRole){/* à voir*/}

  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  switch(index.column()) // revoir l'édition pour ne pas accepter toutes les valeurs et revenir à l'ancien paramètre
  {
  case 0: v_listCue.at(index.row())->m_champ = static_cast<champMM>(value.toInt()); break;
  case 1: v_listCue.at(index.row())->m_p_name = value.toString(); break;
  case 2: v_listCue.at(index.row())->m_p_name2 = value.toString(); break;
  case 3: v_listCue.at(index.row())->m_p_uri = value.toString(); break;
  case 4: v_listCue.at(index.row())->m_p_color = value.toString(); break;
  case 5: v_listCue.at(index.row())->m_p_ID1 = value.toInt(); break;
  case 6: v_listCue.at(index.row())->m_p_ID2 = value.toInt(); break;
  case 7: v_listCue.at(index.row())->m_p_rate = value.toInt(); break;
  case 8: v_listCue.at(index.row())->m_p_opacity = value.toInt(); break;
  case 9: v_listCue.at(index.row())->m_p_volume = value.toInt(); break;
  case 10: v_listCue.at(index.row())->m_m_name = value.toString(); break;
  case 11: v_listCue.at(index.row())->m_m_name2 = value.toString(); break;
  case 12: v_listCue.at(index.row())->m_m_ID1 = value.toInt(); break;
  case 13: v_listCue.at(index.row())->m_m_opacity = value.toInt(); break;
  case 14: v_listCue.at(index.row())->m_m_isvisible = value.toBool(); break;
  case 15: v_listCue.at(index.row())->m_m_issolo = value.toBool(); break;
  case 16: v_listCue.at(index.row())->m_m_islocked = value.toBool(); break;
  case 17: v_listCue.at(index.row())->m_m_depth = value.toInt(); break;
  case 18: v_listCue.at(index.row())->m_isfadein = value.toBool(); break;
  case 19: v_listCue.at(index.row())->m_time = value.toDouble(); break;
  case 20: v_listCue.at(index.row())->m_timeWait = value.toDouble(); break; // if true rajouter remise à zéro de time sauf sur fade
  default: qDebug() << role; break; // Pour éviter unused parameter
  }
  emit dataChanged(index, index);
  return true;
}

QVariant OscCueList::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role==Qt::DisplayRole)
  {
    if (orientation==Qt::Horizontal)
    {
      switch(section)
      {
      case 0: return QString("Champ");
      case 1: return QString("P_name");
      case 2: return QString("p_name2");
      case 3: return QString("Uri");
      case 4: return QString("Color");
      case 5: return QString("P_Id");
      case 6: return QString("P_Id2");
      case 7: return QString("Rate");
      case 8: return QString("P_opac");
      case 9: return QString("Vol");
      case 10: return QString("M_name");
      case 11: return QString("M_name2");
      case 12: return QString("M_Id");
      case 13: return QString("M_opac");
      case 14: return QString("Visible");
      case 15: return QString("Solo");
      case 16: return QString("Lock");
      case 17: return QString("Depth");
      case 18: return QString("Fade_In");
      case 19: return QString("Time");
      case 20: return QString("Wait");
      }
    }
    if (orientation==Qt::Vertical)
      return QString("cue %1").arg(section+1);
  }
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{

  OscSend *tempSend = v_listCue.at(index.row());
  int col = index.column();
  champMM champ = tempSend->m_champ;

  if (col == 0 || col == 20) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
//  else if (tempSend->m_iswaiting == false && col == 19) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  else if (champ == P_NAME) {if (col == 1 || col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_REWIND) {if (col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_REWIND) {if (col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_COLOR) {if (col == 4 || col == 5)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_OPACITY) {if (col == 5 || col == 8)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_VOLUME) {if (col == 5 || col == 9)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_RATE) {if (col == 5 || col == 7)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_URI) {if (col == 3 || col == 5)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_NAME) {if (col == 10 || col == 12)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_OPACITY) {if (col == 12 || col == 13)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_VISIBLE) {if (col == 12 || col == 14)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_SOLO) {if (col == 12 || col == 15)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_LOCK) {if (col == 12 || col == 16)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_DEPTH) {if (col == 12 || col == 17)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_XFADE) {if (col == 5 || col == 6 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_FADE) {if (col == 5 || col == 18 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == R_P_NAME) {if (col == 1 || col == 2)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == R_P_REWIND) {if (col == 1) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_OPACITY) {if (col == 1 || col == 8)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_VOLUME) {if (col == 1 || col == 9)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_RATE) {if (col == 1 || col == 7)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_URI) {if (col == 1 || col == 3)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_COLOR) {if (col == 1 || col == 4)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_NAME) {if (col == 10 || col == 11)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_OPACITY) {if (col == 10 || col == 13)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_VISIBLE) {if (col == 10 || col == 14)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_SOLO) {if (col == 10 || col == 15)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_LOCK) {if (col == 10 || col == 16)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_DEPTH) {if (col ==10 || col == 17)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_FADE) {if (col == 1 || col == 18 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_XFADE) {if (col == 1 || col == 2 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}

  return QAbstractTableModel::flags(index);
}

OscSend* OscCueList::retOscsendFromFileLine(QStringList &lineToken)
{
  champMM m_champ = NOOP;
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

  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    val = val.trimmed();
    qDebug() << val << ", ";
    QVariant value(val);
    switch(j)
    {
    case 0:
      if (val.toStdString() == "NOOP") m_champInt = NOOP;
      if (val.toStdString() == "PLAY") m_champInt = PLAY;
      if (val.toStdString() == "PAUSE") m_champInt = PAUSE;
      if (val.toStdString() == "REWIND") m_champInt = REWIND;
      if (val.toStdString() == "QUIT") m_champInt = QUIT;
      if (val.toStdString() == "P_NAME") m_champInt = P_NAME;
      if (val.toStdString() == "P_REWIND") m_champInt = P_REWIND;
      if (val.toStdString() == "P_OPACITY") m_champInt = P_OPACITY;
      if (val.toStdString() == "P_VOLUME") m_champInt = P_VOLUME;
      if (val.toStdString() == "P_RATE") m_champInt = P_RATE;
      if (val.toStdString() == "P_URI") m_champInt = P_URI;
      if (val.toStdString() == "P_COLOR") m_champInt = P_COLOR;
      if (val.toStdString() == "M_NAME") m_champInt = M_NAME;
      if (val.toStdString() == "M_OPACITY") m_champInt = M_OPACITY;
      if (val.toStdString() == "M_VISIBLE") m_champInt = M_VISIBLE;
      if (val.toStdString() == "M_SOLO") m_champInt = M_SOLO;
      if (val.toStdString() == "M_LOCK") m_champInt = M_LOCK;
      if (val.toStdString() == "M_DEPTH") m_champInt = M_DEPTH;
      if (val.toStdString() == "P_XFADE") m_champInt = P_XFADE;
      if (val.toStdString() == "P_FADE") m_champInt = P_FADE;
      if (val.toStdString() == "R_P_NAME") m_champInt = R_P_NAME;
      if (val.toStdString() == "R_P_REWIND") m_champInt = R_P_REWIND;
      if (val.toStdString() == "R_P_OPACITY") m_champInt = R_P_OPACITY;
      if (val.toStdString() == "R_P_VOLUME") m_champInt = R_P_VOLUME;
      if (val.toStdString() == "R_P_RATE") m_champInt = R_P_RATE;
      if (val.toStdString() == "R_P_URI") m_champInt = R_P_URI;
      if (val.toStdString() == "R_P_COLOR") m_champInt = R_P_COLOR;
      if (val.toStdString() == "R_M_NAME") m_champInt = R_M_NAME;
      if (val.toStdString() == "R_M_OPACITY") m_champInt = R_M_OPACITY;
      if (val.toStdString() == "R_M_VISIBLE") m_champInt = R_M_VISIBLE;
      if (val.toStdString() == "R_M_SOLO") m_champInt = R_M_SOLO;
      if (val.toStdString() == "R_M_LOCK") m_champInt = R_M_LOCK;
      if (val.toStdString() == "R_M_DEPTH") m_champInt = R_M_DEPTH;
      if (val.toStdString() == "R_P_FADE") m_champInt = R_P_FADE;
      if (val.toStdString() == "R_P_XFADE") m_champInt = R_P_XFADE;
      qDebug() << "bluk " << val << " " << m_champInt << " bluk";
      break;
    case 1: m_p_name = value.toString(); break;
    case 2: m_p_name2 = value.toString(); break;
    case 3: m_p_uri = value.toString(); break;
    case 4: m_p_color = value.toString(); break;
    case 5: m_p_ID1 = value.toInt(); break;
    case 6: m_p_ID2 = value.toInt(); break;
    case 7: m_p_rate = value.toInt(); break;
    case 8: m_p_opacity = value.toInt(); break;
    case 9: m_p_volume = value.toInt(); break;
    case 10: m_m_name = value.toString(); break;
    case 11: m_m_name2 = value.toString(); break;
    case 12: m_m_ID1 = value.toInt(); break;
    case 13: m_m_opacity = value.toInt(); break;
    case 14: m_m_isvisible = value.toInt(); break;
    case 15: m_m_issolo = value.toInt(); break;
    case 16: m_m_islocked = value.toInt(); break;
    case 17: m_m_depth = value.toInt(); break;
    case 18: m_isfadein = value.toInt(); break;
    case 19: m_time = value.toDouble(); break;
    case 20: m_timewait = value.toDouble(); break;
    default: break;
    }
  m_champ = static_cast<champMM>(m_champInt);
  }
  qDebug() << m_champ << " bluk2";

  OscSend *oscsend = new OscSend(
        m_champ,
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
        m_timewait
        );

  return oscsend;
}

void OscCueList::addCue(OscSend *oscsend)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, v_listCue.size(), v_listCue.size());
  v_listCue.append(oscsend);
  endInsertRows();

  qDebug() << "cue added";
}

void OscCueList::insertCue(OscSend *oscsend, int row)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, row + 1, row + 1);
  v_listCue.insert(row + 1, oscsend);
  endInsertRows();

  qDebug() << "cue inserted";
}

void OscCueList::moveCuePrev(int rowCue)
{
  QModelIndex indexTemp = QModelIndex();
  beginMoveRows(indexTemp, rowCue, rowCue, indexTemp, rowCue - 1);
  v_listCue.move(rowCue, rowCue - 1);
  endMoveRows();
}

void OscCueList::removeCue(int rowCue)
{
  QModelIndex indexTemp = QModelIndex();
  beginRemoveRows(indexTemp, rowCue, rowCue);
  v_listCue.remove(rowCue);
  endRemoveRows();
}

void OscCueList::removeAllCue()
{
  if (!(v_listCue.size())) return;
  int rows = rowCount();
  for (int i = 0; i < rows; i++)
  {
    removeCue(0);
  }

  qDebug() << "All cue removed";
}
