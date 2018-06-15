#include "osccuelist.h"

OscCueList::OscCueList(QObject *parent):
    QAbstractTableModel(parent)
{
    OscSend *oscTest = new OscSend(NOOP, 1);
    v_listCue.append(oscTest);
    OscSend *oscTest2 = new OscSend(P_OPACITY, 1, 87, 0);
    v_listCue.append(oscTest2);
}

int OscCueList::rowCount(const QModelIndex &) const
{
    return (v_listCue.size());
}

int OscCueList::columnCount(const QModelIndex &) const
{
    return 15;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const
{
    OscSend *tempSend = v_listCue.at(index.row());
    int col = index.column();
    QBrush yellowBackground(Qt::yellow);
    if (role == Qt::DisplayRole)
    {
        //OscSend *tempSend = v_listCue[index.row()];
        //int col = index.column();
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
    switch(index.column()){
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
    case 12: v_listCue.at(index.row())->m_m_depth = value.toBool(); break;
    case 13: v_listCue.at(index.row())->m_time = value.toInt(); break;
    case 14: v_listCue.at(index.row())->m_isfadein = value.toBool(); break;
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

void OscCueList::addCue(OscSend *oscsend)
{
    v_listCue.append(oscsend);

    QModelIndex index;
    for (int i=0; i<15; i++)
    {
        index = createIndex(v_listCue.size(), i);
        switch(i){
        case 0: setData(index, oscsend->m_champ, 0); break;
        case 1: setData(index, oscsend->m_p_uri, 0); break;
        case 2: setData(index, oscsend->m_p_ID1, 0); break;
        case 3: setData(index, oscsend->m_p_ID2, 0); break;
        case 4: setData(index, oscsend->m_p_rate, 0); break;
        case 5: setData(index, oscsend->m_p_opacity, 0); break;
        case 6: setData(index, oscsend->m_p_volume, 0); break;
        case 7: setData(index, oscsend->m_m_ID1, 0); break;
        case 8: setData(index, oscsend->m_m_opacity, 0); break;
        case 9: setData(index, oscsend->m_m_isvisible, 0); break;
        case 10: setData(index, oscsend->m_m_issolo, 0); break;
        case 11: setData(index, oscsend->m_m_islocked, 0); break;
        case 12: setData(index, oscsend->m_m_depth, 0); break;
        case 13: setData(index, oscsend->m_time, 0); break;
        case 14: setData(index, oscsend->m_isfadein, 0); break;
        default: break;
        }
        //emit dataChanged(index, index);
    }

    //setData(topLeft, );
    //emit dataChanged(topLeft, bottomRight);
    std::cout << "cue added" << std::endl;

}
