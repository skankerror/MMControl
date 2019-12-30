#include "tabseq.h"

TabSeq::TabSeq(OscCueList *oscCueList) :
    QWidget(),
    m_oscCueList(oscCueList)
{
    layoutMain = new QHBoxLayout;
    layout1 = new QHBoxLayout;
        boutonLayout = new QVBoxLayout;
            boutonPrev = new QPushButton;
                boutonPrev->setText("<");
            boutonNext = new QPushButton;
                boutonNext->setText(">");
            boutonRemove = new QPushButton;
                boutonRemove->setText("-");
            boutonGo = new QPushButton;
                boutonGo->setText("GO !");
            boutonLayout->addWidget(boutonPrev);
            boutonLayout->addWidget(boutonNext);
            boutonLayout->addWidget(boutonRemove);
            boutonLayout->addWidget(boutonGo);
        tableView = new QTableView();
        tableView->setModel(oscCueList);
        tableView->show();
        tableView->resizeColumnsToContents();
    layout1->addWidget(tableView);
    layoutMain->addLayout(boutonLayout);
    layoutMain->addLayout(layout1);
    this->setLayout(layoutMain);

    connect(boutonGo, SIGNAL(clicked(bool)), SLOT(executeGo()));
    connect(boutonPrev, SIGNAL(clicked(bool)), SLOT(movePrevious()));
    connect(boutonNext, SIGNAL(clicked(bool)), SLOT(moveNext()));
    connect(boutonRemove, SIGNAL(clicked(bool)), SLOT(removeCue()));
}

void TabSeq::executeGo()
{
    // Mettre ici pour enchaîner les cues
    m_oscCueList->v_listCue.at((tableView->currentIndex().row()))->ExecuteSend();
    if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid() == true)
    tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1));
    else tableView->setCurrentIndex(tableView->currentIndex().siblingAtRow(0));

}

void TabSeq::movePrevious()
{
    if (tableView->currentIndex().isValid())
    {
        if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()-1).isValid())
        {
            m_oscCueList->moveCuePrev(tableView->currentIndex().row());
        }
    }
}

void TabSeq::moveNext()
{
    if (tableView->currentIndex().isValid())
    {
        if (tableView->currentIndex().siblingAtRow(tableView->currentIndex().row()+1).isValid())
        {
            m_oscCueList->moveCuePrev(tableView->currentIndex().row() + 1);
        }
    }
}

void TabSeq::removeCue()
{
    if (tableView->currentIndex().isValid())
    {
        m_oscCueList->removeCue(tableView->currentIndex().row());
    }
}
