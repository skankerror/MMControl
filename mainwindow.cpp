#include "mainwindow.h"

MainWindow::MainWindow() :
  QMainWindow()
{
  icon = QIcon(":/graphics/Icon");
  setWindowIcon(icon);
  setWindowTitle("Mapmap Controller");
  setGeometry(400, 200, 1024, 768);
  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::gray);
  setAutoFillBackground(true);
  setPalette(pal);

  state = new MMState(this);
  oscCueList = new OscCueList(this);
  midiIn = new MyMidiIn;

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
  // Manque connects pour p_name et m_name ??
 // connect(p_nameLineEdit, SIGNAL(modified()), SLOT())
}

void MainWindow::createCentralWidget()
{
  tabmidi = new TabMidi(midiIn);
  tabseq = new TabSeq(oscCueList);
  tabmmstate = new TabMMState(state);
  tabwidget = new QTabWidget;

  tabwidget->addTab(tabmidi, "Midi In");
  tabwidget->addTab(tabseq, "Sequencer");
  tabwidget->addTab(tabmmstate, "Mapmap State");

  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::lightGray);
  tabwidget->setAutoFillBackground(true);
  tabwidget->setPalette(pal);

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
  // 10 P_URI
  p_uriLabel = new QLabel("Choose->");
  p_uriPushButton = new QPushButton("File");
  // 5 P_NAME
  p_nameLineEdit = new QLineEdit("New name");
  // 11 P_COLOR
  p_colorLabel = new QLabel("Choose->");
  p_colorPushButton = new QPushButton("Color");
  // 5 P_NAME, 6 P_REWIND, 7 P_OPACITY, 8 P_VOLUME, 9 P_RATE
  // 10 P_URI, 11 P_COLOR, 18 P_XFADE, 19 P_FADE
  p_ID1Label = new QLabel("ID");
  p_ID1SpinBox = new QSpinBox;
  p_ID1SpinBox->setMaximum(100);
  p_ID1SpinBox->setMinimum(1);
  // 18 P_XFADE
  p_ID2Label = new QLabel("ID2");
  p_ID2SpinBox = new QSpinBox;
  p_ID2SpinBox->setMaximum(100);
  p_ID2SpinBox->setMinimum(1);
  // 9 P_RATE
  p_rateLabel = new QLabel("rate %");
  p_rateSpinBox = new QSpinBox;
  p_rateSpinBox->setMaximum(1000);
  p_rateSpinBox->setMinimum(1);
  // 7 P_OPACITY
  p_opacityLabel = new QLabel("opacity %");
  p_opacitySpinBox = new QSpinBox;
  // 8 P_VOLUME
  p_volumeLabel = new QLabel("volume %");
  p_volumeSpinBox = new QSpinBox;
  p_volumeSpinBox->setMaximum(100);
  p_volumeSpinBox->setMinimum(0);
  // 12 M_NAME
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
  layout->addWidget(p_uriLabel);//10 P_URI
  layout->addWidget(p_uriPushButton);//10 P_URI
  layout->addWidget(p_nameLineEdit);//5 P_NAME
  layout->addWidget(p_colorLabel);//11 P_COLOR
  layout->addWidget(p_colorPushButton);//11 P_COLOR
  layout->addWidget(p_ID1Label);//5,6,7,8,9,10,11,18,19 P_* M_*
  layout->addWidget(p_ID1SpinBox);//5,6,7,8,9,10,11,18,19 P_* M_*
  layout->addWidget(p_ID2Label);//18 P_XFADE
  layout->addWidget(p_ID2SpinBox);//18 P_XFADE
  layout->addWidget(p_rateLabel);//9 P_RATE
  layout->addWidget(p_rateSpinBox);//9 P_RATE
  layout->addWidget(p_opacityLabel);//7 P_OPACITY
  layout->addWidget(p_opacitySpinBox);//7 P_OPACITY
  layout->addWidget(p_volumeLabel);//8 P_VOLUME
  layout->addWidget(p_volumeSpinBox);//8 P_VOLUME
  layout->addWidget(m_nameLineEdit);//12 M_NAME
  layout->addWidget(m_IDLabel);//12,13,14,15,16,17 M_*
  layout->addWidget(m_IDSpinBox);//12,13,14,15,16,17 M_*
  layout->addWidget(m_opacityLabel);//13 M_OPACITY
  layout->addWidget(m_opacitySpinBox);//13 M_OPACITY
  layout->addWidget(m_visibleCheckBox);//14 M_VISIBLE
  layout->addWidget(m_soloCheckBox);//15 M_SOLO
  layout->addWidget(m_lockCheckBox);//16 M_LOCK
  layout->addWidget(m_depthLabel);//17 M_DEPTH
  layout->addWidget(m_depthSpinBox);//17 M_DEPTH
  layout->addWidget(timeLabel);// TOUS
  layout->addWidget(timeSpinBox);// TOUS
  layout->addWidget(fadeCheckBox);//19 P_FADE
  layout->addStretch();
  layout->addWidget(sendPushButton);
  layout->addWidget(addToCuePushButton);

  myToolBarWidget->setLayout(layout);

  myToolBar->addWidget(myToolBarWidget);

  // On cache tout et on montre suivant les besoins
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
  case NOOP: case PLAY: case PAUSE: case REWIND: case QUIT:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_NAME:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_REWIND:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_OPACITY:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->show();
    p_opacitySpinBox->show(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_VOLUME:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->show(); p_volumeSpinBox->show(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_RATE:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->show(); p_rateSpinBox->show(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_URI:
    p_uriLabel->show(); p_uriPushButton->show(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_COLOR:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->show();
    p_colorPushButton->show(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_NAME:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_OPACITY:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->show(); m_opacitySpinBox->show();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_VISIBLE:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->show(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_SOLO:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->show(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_LOCK:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->show(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case M_DEPTH:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->show();
    m_depthSpinBox->show(); fadeCheckBox->hide(); break;
  case P_XFADE:
    p_uriLabel->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLabel->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->show();
    p_ID2SpinBox->show(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  case P_FADE:
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
  case NOOP: case PLAY: case PAUSE: case REWIND: case QUIT: oscsend = new OscSend(index); break;
    // cstr 2
  case P_NAME: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_nameLineEdit->text()); break;
  case M_NAME: oscsend = new OscSend(index, m_IDSpinBox->value(), m_nameLineEdit->text()); break;
  case P_URI:
    while (p_uriLabel->text() == "Choose->")
      setP_UriLabel();
    oscsend = new OscSend(index, p_ID1SpinBox->value(), p_uriLabel->text());
    break;
    // cstr 3
  case P_REWIND: oscsend = new OscSend(index, p_ID1SpinBox->value(), 0); break;
    // cstr 4
  case P_OPACITY: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_opacitySpinBox->value(), 0); break;
  case P_VOLUME: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_volumeSpinBox->value(), 0); break;
  case P_RATE: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_rateSpinBox->value(), 0); break;
  case M_OPACITY: oscsend = new OscSend(index, m_IDSpinBox->value(), m_opacitySpinBox->value(), 0); break;
  case M_DEPTH: oscsend = new OscSend(index, m_IDSpinBox->value(), m_depthSpinBox->value(), 0); break;
  case P_XFADE: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_ID2SpinBox->value(), timeSpinBox->value()); break;
    // cstr 5
  case P_COLOR:
    while (p_colorLabel->text() == "Choose->")
      setP_ColorLabel();
    oscsend = new OscSend(index, p_ID1SpinBox->value(), p_colorLabel->text());
    break;
    // cstr 6
  case M_VISIBLE: oscsend = new OscSend(index, m_IDSpinBox->value(), m_visibleCheckBox->isChecked()); break;
  case M_SOLO: oscsend = new OscSend(index, m_IDSpinBox->value(), m_soloCheckBox->isChecked()); break;
  case M_LOCK: oscsend = new OscSend(index, m_IDSpinBox->value(), m_lockCheckBox->isChecked()); break;
  case P_FADE: oscsend = new OscSend(index, p_ID1SpinBox->value(), fadeCheckBox->isChecked(), timeSpinBox->value()); break;
  default: oscsend = new OscSend(index); break;
  }
  oscsend->ExecuteSend();
}
void MainWindow::setP_UriLabel()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Choose File",
                                                  "/home/ray/boulot",
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
  champMM index = static_cast<champMM>(champComboBox->currentIndex());
  OscSend *oscsend;
  switch (index)
  {
  // cstr 1
  case NOOP: case PLAY: case PAUSE: case REWIND: case QUIT: oscsend = new OscSend(index); break;
    // cstr 2
  case P_NAME: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_nameLineEdit->text()); break;
  case M_NAME: oscsend = new OscSend(index, m_IDSpinBox->value(), m_nameLineEdit->text()); break;
  case P_URI:
    while (p_uriLabel->text() == "Choose->")
      setP_UriLabel();
    oscsend = new OscSend(index, p_ID1SpinBox->value(), p_uriLabel->text());
    break;
    // cstr 3
  case P_REWIND: oscsend = new OscSend(index, p_ID1SpinBox->value(), 0); break;
    // cstr 4
  case P_OPACITY: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_opacitySpinBox->value(), 0); break;
  case P_VOLUME: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_volumeSpinBox->value(), 0); break;
  case P_RATE: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_rateSpinBox->value(), 0); break;
  case M_OPACITY: oscsend = new OscSend(index, m_IDSpinBox->value(), m_opacitySpinBox->value(), 0); break;
  case M_DEPTH: oscsend = new OscSend(index, m_IDSpinBox->value(), m_depthSpinBox->value(), 0); break;
  case P_XFADE: oscsend = new OscSend(index, p_ID1SpinBox->value(), p_ID2SpinBox->value(), timeSpinBox->value()); break;
    // cstr 5
  case P_COLOR:
    while (p_colorLabel->text() == "Choose->")
      setP_ColorLabel();
    oscsend = new OscSend(index, p_ID1SpinBox->value(), p_colorLabel->text());
    break;
    // cstr 6
  case M_VISIBLE: oscsend = new OscSend(index, m_IDSpinBox->value(), m_visibleCheckBox->isChecked()); break;
  case M_SOLO: oscsend = new OscSend(index, m_IDSpinBox->value(), m_soloCheckBox->isChecked()); break;
  case M_LOCK: oscsend = new OscSend(index, m_IDSpinBox->value(), m_lockCheckBox->isChecked()); break;
  case P_FADE: oscsend = new OscSend(index, p_ID1SpinBox->value(), fadeCheckBox->isChecked(), timeSpinBox->value()); break;
  default: oscsend = new OscSend(index); break;
  }
  oscCueList->addCue(oscsend);
}
