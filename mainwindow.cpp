#include "mainwindow.h"

MainWindow::MainWindow() :
    QMainWindow()
{
    MMState state;
    oscCueList = new OscCueList(this);

    createToolBar();
    createCentralWidget();

    // connect pour afficher les bons widgets sur la toolbar
    connect(champComboBox, SIGNAL(currentIndexChanged(int)), SLOT(showWidgets(int)));
    // Connect pour send
    connect(sendPushButton, SIGNAL(clicked()), SLOT(sendFromToolBar()));
    // Connect pour l'uri
    connect(p_uriPushButton, SIGNAL(clicked()), SLOT(setP_UriLabel()));
    // Connect pour Color
    connect(p_colorPushButton, SIGNAL(clicked()), SLOT(setP_ColorLabel()));
    // Connect pour AddToCue
    connect(addToCuePushButton, SIGNAL(clicked()), SLOT(addToCue()));
}

void MainWindow::createCentralWidget()
{
    tabmidi = new TabMidi;
    tabseq = new TabSeq(oscCueList);
    tabmmstate = new TabMMState;
    tabwidget = new QTabWidget;

    tabwidget->addTab(tabmidi, "Midi In");
    tabwidget->addTab(tabseq, "Sequencer");
    tabwidget->addTab(tabmmstate, "Mapmap State");

    setCentralWidget(tabwidget);
}
void MainWindow::createToolBar()
{
    myToolBar = addToolBar("MessageToolBar");
    QWidget *myToolBarWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
        // tout le temps
        champLabel = new QLabel("champ");
        champComboBox = new QComboBox;
            champComboBox->addItem("NOOP");//0
            champComboBox->addItem("PLAY");//1
            champComboBox->addItem("PAUSE");//2
            champComboBox->addItem("REWIND");//3
            champComboBox->addItem("QUIT");//4
            champComboBox->addItem("P_NAME");//5
            champComboBox->addItem("P_REWIND");//6
            champComboBox->addItem("P_OPACITY");//7
            champComboBox->addItem("P_VOLUME");//8
            champComboBox->addItem("P_RATE");//9
            champComboBox->addItem("P_URI");//10
            champComboBox->addItem("P_COLOR");//11
            champComboBox->addItem("M_NAME");//12
            champComboBox->addItem("M_OPACITY");//13
            champComboBox->addItem("M_VISIBLE");//14
            champComboBox->addItem("M_SOLO");//15
            champComboBox->addItem("M_LOCK");//16
            champComboBox->addItem("M_DEPTH");//17
            champComboBox->addItem("P_XFADE");//18
            champComboBox->addItem("P_FADE");//19
            champComboBox->setCurrentIndex(0);
        // 10
        p_uriLabel = new QLabel("Choose->");
        p_uriPushButton = new QPushButton("File");
        // 5
        p_nameLineEdit = new QLineEdit("New name");
        // 11
        p_colorLabel = new QLabel("Choose->");
        p_colorPushButton = new QPushButton("Color");
        // 5, 6, 7, 8, 9, 10, 11, 18, 19
        p_ID1Label = new QLabel("ID");
        p_ID1SpinBox = new QSpinBox;
            p_ID1SpinBox->setMaximum(100);
            p_ID1SpinBox->setMinimum(1);
        // 18
        p_ID2Label = new QLabel("ID2");
        p_ID2SpinBox = new QSpinBox;
            p_ID2SpinBox->setMaximum(100);
            p_ID2SpinBox->setMinimum(1);
        // 9
        p_rateLabel = new QLabel("rate %");
        p_rateSpinBox = new QSpinBox;
            p_rateSpinBox->setMaximum(1000);
            p_rateSpinBox->setMinimum(1);
        // 7
        p_opacityLabel = new QLabel("opacity %");
        p_opacitySpinBox = new QSpinBox;
        // 8
        p_volumeLabel = new QLabel("volume %");
        p_volumeSpinBox = new QSpinBox;
            p_volumeSpinBox->setMaximum(100);
            p_volumeSpinBox->setMinimum(0);
        // 12
        m_nameLineEdit = new QLineEdit("New name");
        // 12, 13, 14, 15, 16, 17
        m_IDLabel = new QLabel("ID");
        m_IDSpinBox = new QSpinBox;
            m_IDSpinBox->setMaximum(100);
            m_IDSpinBox->setMinimum(1);
        // 13
        m_opacityLabel = new QLabel("opacity %");
        m_opacitySpinBox = new QSpinBox;
            m_opacitySpinBox->setMaximum(100);
            m_opacitySpinBox->setMinimum(0);
        // 14
        m_visibleCheckBox = new QCheckBox("Visible");
        // 15
        m_soloCheckBox = new QCheckBox("Solo");
        // 16
        m_lockCheckBox = new QCheckBox("Lock");
        // 17
        m_depthLabel = new QLabel("depth");
        m_depthSpinBox = new QSpinBox;
        // tout le temps
        timeLabel = new QLabel("time");
        timeSpinBox = new QSpinBox;
            timeSpinBox->setMaximum(1000);
        // 19
        fadeCheckBox = new QCheckBox("fade in");
        // tout le temps
        sendPushButton = new QPushButton("Send !");
        addToCuePushButton = new QPushButton("Add to Cue !");

    layout->addWidget(champLabel);
    layout->addWidget(champComboBox);
    layout->addWidget(p_uriLabel);//10
    layout->addWidget(p_uriPushButton);//10
    layout->addWidget(p_nameLineEdit);//5
    layout->addWidget(p_colorLabel);//11
    layout->addWidget(p_colorPushButton);//11
    layout->addWidget(p_ID1Label);//5,6,7,8,9,10,11,18,19
    layout->addWidget(p_ID1SpinBox);//5,6,7,8,9,10,11,18,19
    layout->addWidget(p_ID2Label);//18
    layout->addWidget(p_ID2SpinBox);//18
    layout->addWidget(p_rateLabel);//9
    layout->addWidget(p_rateSpinBox);//9
    layout->addWidget(p_opacityLabel);//7
    layout->addWidget(p_opacitySpinBox);//7
    layout->addWidget(p_volumeLabel);//8
    layout->addWidget(p_volumeSpinBox);//8
    layout->addWidget(m_nameLineEdit);//12
    layout->addWidget(m_IDLabel);//12,13,14,15,16,17
    layout->addWidget(m_IDSpinBox);//12,13,14,15,16,17
    layout->addWidget(m_opacityLabel);//13
    layout->addWidget(m_opacitySpinBox);//13
    layout->addWidget(m_visibleCheckBox);//14
    layout->addWidget(m_soloCheckBox);//15
    layout->addWidget(m_lockCheckBox);//16
    layout->addWidget(m_depthLabel);//17
    layout->addWidget(m_depthSpinBox);//17
    layout->addWidget(timeLabel);// sauf 0
    layout->addWidget(timeSpinBox);// sauf 0
    layout->addWidget(fadeCheckBox);//19
    layout->addStretch();
    layout->addWidget(sendPushButton);
    layout->addWidget(addToCuePushButton);

    myToolBarWidget->setLayout(layout);

    myToolBar->addWidget(myToolBarWidget);

    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide();

}
void MainWindow::showWidgets(int index)
{
    switch (index)
    {
    case 0: case 1: case 2: case 3: case 4:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 5:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 6:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 7:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->show();
        p_opacitySpinBox->show(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 8:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->show(); p_volumeSpinBox->show(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 9:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->show(); p_rateSpinBox->show(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 10:
        p_uriLabel->show(); p_uriPushButton->show(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 11:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->show();
        p_colorPushButton->show(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 12:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 13:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->show(); m_opacitySpinBox->show();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 14:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->show(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 15:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->show(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 16:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->show(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 17:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->show();
        m_depthSpinBox->show(); fadeCheckBox->hide(); break;
    case 18:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->show();
        p_ID2SpinBox->show(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
    case 19:
        p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
        p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
        p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
        p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
        m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
        m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
        m_depthSpinBox->hide(); fadeCheckBox->show(); break;
    default: break;
    }
}
void MainWindow::sendFromToolBar()
{
    champMM index = static_cast<champMM>(champComboBox->currentIndex());
    OscSend *oscsend;
    switch (index)
    {
    // cstr 1
    case 0: case 1: case 2: case 3: case 4: oscsend = new OscSend(index); break;
    // cstr 2
    case 5: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_nameLineEdit->text()); break;
    case 12: oscsend = new OscSend(index, m_IDSpinBox->value(), m_nameLineEdit->text()); break;
    case 10:
        while (p_uriLabel->text() == "Choose->")
            setP_UriLabel();
        oscsend = new OscSend(index, p_ID1SpinBox->value(), p_uriLabel->text());
        break;
    // cstr 3
    case 6: oscsend = new OscSend(index, p_ID1SpinBox->value(), 0); break;
    // cstr 4
    case 7: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_opacitySpinBox->value(), 0); break;
    case 8: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_volumeSpinBox->value(), 0); break;
    case 9: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_rateSpinBox->value(), 0); break;
    case 13: oscsend = new OscSend(index, m_IDSpinBox->value(), m_opacitySpinBox->value(), 0); break;
    case 17: oscsend = new OscSend(index, m_IDSpinBox->value(), m_depthSpinBox->value(), 0); break;
    case 18: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_ID2SpinBox->value(), timeSpinBox->value()); break;
    // cstr 5
    case 11:
        while (p_colorLabel->text() == "Choose->")
            setP_ColorLabel();
        oscsend = new OscSend(index, p_ID1SpinBox->value(), p_colorLabel->text());
        break;
    // cstr 6
    case 14: oscsend = new OscSend(index, m_IDSpinBox->value(), m_visibleCheckBox->isChecked()); break;
    case 15: oscsend = new OscSend(index, m_IDSpinBox->value(), m_soloCheckBox->isChecked()); break;
    case 16: oscsend = new OscSend(index, m_IDSpinBox->value(), m_lockCheckBox->isChecked()); break;
    case 19: oscsend = new OscSend(index, p_ID1SpinBox->value(), fadeCheckBox->isChecked(), timeSpinBox->value()); break;
    default: oscsend = new OscSend(index); break;
    }
    oscsend->ExecuteSend();
}
void MainWindow::setP_UriLabel()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose File",
                                                         "/home/ray/Boulot",
                                                         "Media Files (*.png, *.jpg, *.gif, *.mov, *.avi, *.mp4");
    p_uriLabel->setText(fileName);
}
void MainWindow::setP_ColorLabel()
{
    QColor colorTemp = QColorDialog::getColor();
    p_colorLabel->setText(colorTemp.name());
}
void MainWindow::addToCue()
{
    //if (une cue est sélectionnée...
    champMM index = static_cast<champMM>(champComboBox->currentIndex());
    OscSend *oscsend;
    switch (index)
    {
    // cstr 1
    case 0: case 1: case 2: case 3: case 4: oscsend = new OscSend(index); break;
    // cstr 2
    case 5: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_nameLineEdit->text()); break;
    case 12: oscsend = new OscSend(index, m_IDSpinBox->value(), m_nameLineEdit->text()); break;
    case 10:
        while (p_uriLabel->text() == "Choose->")
            setP_UriLabel();
        oscsend = new OscSend(index, p_ID1SpinBox->value(), p_uriLabel->text());
        break;
    // cstr 3
    case 6: oscsend = new OscSend(index, p_ID1SpinBox->value(), 0); break;
    // cstr 4
    case 7: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_opacitySpinBox->value(), 0); break;
    case 8: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_volumeSpinBox->value(), 0); break;
    case 9: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_rateSpinBox->value(), 0); break;
    case 13: oscsend = new OscSend(index, m_IDSpinBox->value(), m_opacitySpinBox->value(), 0); break;
    case 17: oscsend = new OscSend(index, m_IDSpinBox->value(), m_depthSpinBox->value(), 0); break;
    case 18: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_ID2SpinBox->value(), timeSpinBox->value()); break;
    // cstr 5
    case 11:
        while (p_colorLabel->text() == "Choose->")
            setP_ColorLabel();
        oscsend = new OscSend(index, p_ID1SpinBox->value(), p_colorLabel->text());
        break;
    // cstr 6
    case 14: oscsend = new OscSend(index, m_IDSpinBox->value(), m_visibleCheckBox->isChecked()); break;
    case 15: oscsend = new OscSend(index, m_IDSpinBox->value(), m_soloCheckBox->isChecked()); break;
    case 16: oscsend = new OscSend(index, m_IDSpinBox->value(), m_lockCheckBox->isChecked()); break;
    case 19: oscsend = new OscSend(index, p_ID1SpinBox->value(), fadeCheckBox->isChecked(), timeSpinBox->value()); break;
    default: oscsend = new OscSend(index); break;
    }
    oscCueList->addCue(oscsend);
}
