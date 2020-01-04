#include "osccuelist.h"

OscCueList::OscCueList(QObject *parent):
  QAbstractTableModel(parent)
{}

int OscCueList::rowCount(const QModelIndex &) const
{
  return (v_listCue.size());
}

int OscCueList::columnCount(const QModelIndex &) const
{
  return 16;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const
{
  OscSend *tempSend = v_listCue.at(index.row());
  int col = index.column();
  QBrush yellowBackground(Qt::yellow);
  if (role == Qt::DisplayRole)
  {
    switch (col) {
    case 0:
      switch(tempSend->m_champ) {
      case NOOP: return QString("NOOP");
      case PLAY: return QString("PLAY");
      case PAUSE: return QString("PAUSE");
      case REWIND: return QString("REWIND");
      case QUIT: return QString("QUIT");
      case P_NAME: return QString("P_NAME");
      case P_REWIND: return QString("P_REWIND");
      case P_OPACITY: return QString("P_OPACITY");
      case P_VOLUME: return QString("P_VOLUME");
      case P_RATE: return QString("P_RATE");
      case P_URI: return QString("P_URI");
      case P_COLOR: return QString("P_COLOR");
      case M_NAME: return QString("M_NAME");
      case M_OPACITY: return QString("M_OPACITY");
      case M_VISIBLE: return QString("M_VISIBLE");
      case M_SOLO: return QString("M_SOLO");
      case M_LOCK: return QString("M_LOCK");
      case M_DEPTH: return QString("M_DEPTH");
      case P_XFADE: return QString("P_XFADE");
      case P_FADE: return QString("P_FADE");
      default: break;
      }
      break;
    case 1: return tempSend->m_p_uri;
    case 2: return QString::number(tempSend->m_p_ID1);
    case 3: return QString::number(tempSend->m_p_ID2);
    case 4: return QString::number(tempSend->m_p_rate);
    case 5: return QString::number(tempSend->m_p_opacity);
    case 6: return QString::number(tempSend->m_p_volume);
    case 7: return QString::number(tempSend->m_m_ID1);
    case 8: return QString::number(tempSend->m_m_opacity);
    case 9: return QString::number(tempSend->m_m_isvisible);
    case 10: return QString::number(tempSend->m_m_issolo);
    case 11: return QString::number(tempSend->m_m_islocked);
    case 12: return QString::number(tempSend->m_m_depth);
    case 13: return QString::number(tempSend->m_time);
    case 14: return QString::number(tempSend->m_isfadein);
    case 15: return QString::number(tempSend->m_iswaiting);
    default:
      break;
    }

  }
  if (role == Qt::BackgroundRole)
  {
    if(col==0||col==13) return yellowBackground;
    switch(tempSend->m_champ){
    //case NOOP: case PLAY: case PAUSE: case REWIND: case QUIT: if(col==13) return yellowBackground;
    case P_NAME: if(col==1||col==2) return yellowBackground; break;
    case P_REWIND: case P_COLOR: if(col==2) return yellowBackground; break;
    case P_OPACITY: if(col==2||col==5) return yellowBackground; break;
    case P_VOLUME: if(col==2||col==6) return yellowBackground; break;
    case P_RATE: if(col==2||col==4) return yellowBackground; break;
    case P_URI: if(col==1||col==2) return yellowBackground; break;
    case M_NAME: if(col==7) return yellowBackground; break;
    case M_OPACITY: if(col==7||col==8) return yellowBackground; break;
    case M_VISIBLE: if(col==7||col==9) return yellowBackground; break;
    case M_SOLO: if(col==7||col==10) return yellowBackground; break;
    case M_LOCK: if(col==7||col==11) return yellowBackground; break;
    case M_DEPTH: if(col==7||col==12) return yellowBackground; break;
    case P_XFADE: if(col==2||col==3||col==14) return yellowBackground; break;
    case P_FADE: if(col==2||col==14) return yellowBackground; break;
    default: break;
    }
  }
  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  switch(index.column())
  {
  case 0: v_listCue.at(index.row())->m_champ = static_cast<champMM>(value.toInt()); break;
  case 1: v_listCue.at(index.row())->m_p_uri = value.toString(); break;
  case 2: v_listCue.at(index.row())->m_p_ID1 = value.toInt(); break;
  case 3: v_listCue.at(index.row())->m_p_ID2 = value.toInt(); break;
  case 4: v_listCue.at(index.row())->m_p_rate = value.toInt(); break;
  case 5: v_listCue.at(index.row())->m_p_opacity = value.toInt(); break;
  case 6: v_listCue.at(index.row())->m_p_volume = value.toInt(); break;
  case 7: v_listCue.at(index.row())->m_m_ID1 = value.toInt(); break;
  case 8: v_listCue.at(index.row())->m_m_opacity = value.toInt(); break;
  case 9: v_listCue.at(index.row())->m_m_isvisible = value.toBool(); break;
  case 10: v_listCue.at(index.row())->m_m_issolo = value.toBool(); break;
  case 11: v_listCue.at(index.row())->m_m_islocked = value.toBool(); break;
  case 12: v_listCue.at(index.row())->m_m_depth = value.toBool(); break; // ???
  case 13: v_listCue.at(index.row())->m_time = value.toInt(); break;
  case 14: v_listCue.at(index.row())->m_isfadein = value.toBool(); break;
  case 15: v_listCue.at(index.row())->m_iswaiting = value.toBool(); break;
  default: break;
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
      case 1: return QString("p_uri");
      case 2: return QString("p_ID1");
      case 3: return QString("p_ID2");
      case 4: return QString("p_rate");
      case 5: return QString("p_opac");
      case 6: return QString("p_vol");
      case 7: return QString("m_ID");
      case 8: return QString("m_opac");
      case 9: return QString("m_vis");
      case 10: return QString("m_solo");
      case 11: return QString("m_lock");
      case 12: return QString("m_depth");
      case 13: return QString("time");
      case 14: return QString("fadeIn");
      case 15: return QString("wait");
      }
    }
    if (orientation==Qt::Vertical)
      return QString("cue %1").arg(section+1);
  }
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

OscSend* OscCueList::retOscsendFromFileLine(QStringList &lineToken)
{
  OscSend *oscsend;
  champMM m_champ;
  int m_champInt;
  QString m_p_uri = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0;
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  bool m_m_depth = false; // ???
  int m_time = 0;
  bool m_isfadein = false;
  bool m_iswaiting = false;

  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    std::cout << val.toStdString() << ", ";
    QVariant value(val);
//    int m_champInt;
    switch(j)
    {
//    case 0: m_champ = static_cast<champMM>(value.toInt()); std::cout << m_champ << "bluk"; break;
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
      //else m_champInt = NOOP;
      //int champInt = static_cast<champMM>(m_champ);
      std::cout << "bluk" << val.toStdString()<< " " << m_champInt << "bluk";
      break;
    case 1: m_p_uri = value.toString(); break;
    case 2: m_p_ID1 = value.toInt(); break;
    case 3: m_p_ID2 = value.toInt(); break;
    case 4: m_p_rate = value.toInt(); break;
    case 5: m_p_opacity = value.toInt(); break;
    case 6: m_p_volume = value.toInt(); break;
    case 7: m_m_ID1 = value.toInt(); break;
    case 8: m_m_opacity = value.toInt(); break;
    case 9: m_m_isvisible = value.toBool(); break;
    case 10: m_m_issolo = value.toBool(); break;
    case 11: m_m_islocked = value.toBool(); break;
    case 12: m_m_depth = value.toBool(); break; // ???
    case 13: m_time = value.toInt(); break;
    case 14: m_isfadein = value.toBool(); break;
    case 15: m_iswaiting = value.toBool(); break;
    default: break;
    }
  m_champ = static_cast<champMM>(m_champInt);
  }
//  m_champ = static_cast<champMM>(m_champInt);
  std::cout << m_champ << "bluk2";
  switch(m_champInt)
  {
  case 0: case 1: case 2: case 3: case 4: oscsend = new OscSend(m_champ); break;
    // cstr 2
  case 5: oscsend = new OscSend(m_champ, m_p_ID1, m_p_uri); break;
  case 12: oscsend = new OscSend(m_champ, m_m_ID1, m_p_uri); break;
  case 10: oscsend = new OscSend(m_champ, m_p_ID1, m_p_uri); break;
    // cstr 3
  case 6: oscsend = new OscSend(m_champ, m_p_ID1, 0); break;
    // cstr 4
  case 7: oscsend = new OscSend(m_champ, m_p_ID1, m_p_opacity, 0); break;
  case 8: oscsend = new OscSend(m_champ, m_p_ID1, m_p_volume, 0); break;
  case 9: oscsend = new OscSend(m_champ, m_p_ID1, m_p_rate, 0); break;
  case 13: oscsend = new OscSend(m_champ, m_m_ID1, m_m_opacity, 0); break;
  case 17: oscsend = new OscSend(m_champ, m_m_ID1, m_m_depth, 0); break;
  case 18: oscsend = new OscSend(m_champ, m_p_ID1, m_p_ID2, m_time); break;
    // cstr 5
  case 11: oscsend = new OscSend(m_champ, m_p_ID1, m_p_uri); break;
    // cstr 6
  case 14: oscsend = new OscSend(m_champ, m_m_ID1, m_m_isvisible); break;
  case 15: oscsend = new OscSend(m_champ, m_m_ID1, m_m_issolo); break;
  case 16: oscsend = new OscSend(m_champ, m_m_ID1, m_m_islocked); break;
  case 19: oscsend = new OscSend(m_champ, m_p_ID1, m_isfadein, m_time); break;
  default: oscsend = new OscSend(m_champ); break;
  }
  // renvoyer les oscsend...

  return oscsend;
}

void OscCueList::addCue(OscSend *oscsend)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, v_listCue.size(), v_listCue.size());
  v_listCue.append(oscsend);
  endInsertRows();

  std::cout << "cue added" << std::endl;

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

