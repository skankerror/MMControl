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

#include "mainwindow.h"

MainWindow::MainWindow() :
  QMainWindow()
{
  icon = QIcon(":/graphics/Icon");
  setWindowIcon(icon);
  setWindowTitle(WINDOW_TITLE);
  setGeometry(X_WINDOW_OFFSET, Y_WINDOW_OFFSET, WINDOW_WIDTH, WINDOW_HEIGHT);

  state = new MMState(this);
  oscCueList = new OscCueList(this);

  midiIn1 = new MyMidiIn(this);
  midiIn2 = new MyMidiIn(this);
  midiOut1 = new MyMidiOut(this);
  midiOut2 = new MyMidiOut(this);
  treeView = new QTreeView(this);
  createToolBar();
  createCentralWidget();
  createStatusBar();

  progressBarCue->reset();
  progressBarSend->reset();

  connect(champComboBox, SIGNAL(currentIndexChanged(int)), SLOT(showWidgets(int))); // Pour afficher les widgets
  connect(sendPushButton, SIGNAL(clicked()), SLOT(sendFromToolBar()));
  connect(p_uriPushButton, SIGNAL(clicked()), SLOT(setP_UriLine()));
  connect(p_colorPushButton, SIGNAL(clicked()), SLOT(setP_ColorLine()));
  connect(addToCuePushButton, SIGNAL(clicked()), SLOT(addToCue()));

  connect(tabseq, SIGNAL(updateProgressTimeCue(int)), this, SLOT(timeProgressedCue(int)));
  connect(tabseq, SIGNAL(progressTimeFinishedCue()), this, SLOT(timeFinishedCue()));
  connect(tabseq, SIGNAL(updateProgressTimeSend(int)), this, SLOT(timeProgressedSend(int)));
  connect(tabseq, SIGNAL(progressTimeFinishedSend()), this, SLOT(timeFinishedSend()));
  connect(tabseq, SIGNAL(updateProgressTimeWaitSend(int)), this, SLOT(timeProgressedSend(int)));
  connect(tabseq, SIGNAL(progressTimeWaitFinishedSend()), this, SLOT(timeFinishedSend()));
  connect(tabseq, SIGNAL(sendStringToOutputLabel(QString)), outputLabel, SLOT(setText(QString)));
  connect(tabmidi, SIGNAL(sendStringToOutputLabel(QString)), outputLabel, SLOT(setText(QString)));

}

void MainWindow::createCentralWidget()
{
  tabmidi = new TabMidi(midiIn1, midiIn2, midiOut1, midiOut2, this);
  tabseq = new TabSeq(oscCueList, treeView, midiIn1, midiIn2, midiOut1, midiOut2, /*progressBarCue, */this);
  tabmmstate = new TabMMState(state, this);
  tabwidget = new QTabWidget(this);

  tabwidget->addTab(tabmidi, "Midi In");
  tabwidget->addTab(tabseq, "Sequencer");
  tabwidget->addTab(tabmmstate, "Mapmap State");

  setCentralWidget(tabwidget);
}
void MainWindow::createToolBar()
{
  myToolBar = addToolBar("MessageToolBar");
  auto *myToolBarWidget = new QWidget(this);
  auto *layout = new QHBoxLayout();
  // tout le temps
  champLabel = new QLabel("champ", this);
  champComboBox = new QComboBox(this);
  for (int i = 0; i < CUE; i++) champComboBox->addItem(OscSend::getChampToString(i));
  champComboBox->setCurrentIndex(PLAY);

  // P_NAME, R_P_NAME, R_P_REWIND, R_P_OPACITY, R_P_VOLUME, R_P_RATE, R_P_URI, R_P_COLOR, R_P_FADE, R_P_XFADE
  p_nameLineEdit = new QLineEdit("Name", this);
  // R_P_NAME, R_P_XFADE
  p_nameLineEdit2 = new QLineEdit("Name2", this);
  // P_URI, R_P_URI
  p_uriLine = new QLineEdit("Choose->", this);
  p_uriPushButton = new QPushButton("File", this);
  // P_COLOR
  p_colorLine = new QLineEdit("Choose->", this);
  p_colorPushButton = new QPushButton("Color", this);
  // P_NAME, P_REWIND, P_OPACITY, P_VOLUME, P_RATE, P_URI, P_COLOR, P_XFADE, P_FADE
  p_ID1Label = new QLabel("ID", this);
  p_ID1SpinBox = new QSpinBox(this);
  p_ID1SpinBox->setMaximum(100);
  p_ID1SpinBox->setMinimum(1);
  // P_XFADE
  p_ID2Label = new QLabel("ID2", this);
  p_ID2SpinBox = new QSpinBox(this);
  p_ID2SpinBox->setMaximum(100);
  p_ID2SpinBox->setMinimum(1);
  p_ID2SpinBox->setValue(2);
  // P_RATE, R_P_RATE
  p_rateLabel = new QLabel("rate %", this);
  p_rateSpinBox = new QSpinBox(this);
  p_rateSpinBox->setMaximum(1000);
  p_rateSpinBox->setMinimum(-1000);
  // P_OPACITY, R_P_OPACITY
  p_opacityLabel = new QLabel("opacity %", this);
  p_opacitySpinBox = new QSpinBox(this);
  p_opacitySpinBox->setMaximum(100);
  p_opacitySpinBox->setMinimum(0);
  // P_VOLUME, R_P_VOLUME
  p_volumeLabel = new QLabel("volume %", this);
  p_volumeSpinBox = new QSpinBox(this);
  p_volumeSpinBox->setMaximum(100);
  p_volumeSpinBox->setMinimum(0);
  // M_NAME, R_M_NAME, R_M_OPACITY, R_M_VISIBLE, R_M_SOLO, R_M_LOCK, R_M_DEPTH,
  m_nameLineEdit = new QLineEdit("Name", this);
  // R_M_NAME
  m_nameLineEdit2 = new QLineEdit("Name2", this);
  // M_NAME, M_OPACITY, M_VISIBLE, M_SOLO, M_LOCK, M_DEPTH
  m_IDLabel = new QLabel("ID", this);
  m_IDSpinBox = new QSpinBox(this);
  m_IDSpinBox->setMaximum(100);
  m_IDSpinBox->setMinimum(1);
  // M_OPACITY, R_M_OPACITY
  m_opacityLabel = new QLabel("opacity %", this);
  m_opacitySpinBox = new QSpinBox(this);
  m_opacitySpinBox->setMaximum(100);
  m_opacitySpinBox->setMinimum(0);
  // M_VISIBLE, R_M_VISIBLE
  m_visibleCheckBox = new QCheckBox("Visible", this);
  // M_SOLO, R_M_SOLO
  m_soloCheckBox = new QCheckBox("Solo", this);
  // M_LOCK, R_M_LOCK
  m_lockCheckBox = new QCheckBox("Lock", this);
  // M_DEPTH, R_M_DEPTH
  m_depthLabel = new QLabel("depth", this);
  m_depthSpinBox = new QSpinBox(this);
  // tout le temps ??
  timeLabel = new QLabel("time in s", this);
  timeSpinBox = new QDoubleSpinBox(this);
  timeSpinBox->setMaximum(1000);
  timeSpinBox->setMinimum(0);
  timeSpinBox->setDecimals(1);
  timeSpinBox->setValue(2);
  // P_FADE, R_P_FADE
  fadeCheckBox = new QCheckBox("fade in", this);
  // tout le temps
  waitTimeLabel = new QLabel("waitTime in s", this);
  waitTimeSpinBox = new QDoubleSpinBox(this);
  waitTimeSpinBox->setMaximum(1000);
  waitTimeSpinBox->setMinimum(0);
  waitTimeSpinBox->setDecimals(1);
  waitTimeSpinBox->setValue(0);

  sendPushButton = new QPushButton("Send !", this);
  sendPushButton->setToolTip("Directly send to mapmap");
  sendPushButton->setToolTipDuration(2000);
  addToCuePushButton = new QPushButton("Add to Cue !", this);
  addToCuePushButton->setToolTip("Add to cue in sequencer tab");
  addToCuePushButton->setToolTipDuration(2000);

  layout->addWidget(champLabel); layout->addWidget(champComboBox); layout->addWidget(p_nameLineEdit);
  layout->addWidget(p_nameLineEdit2); layout->addWidget(p_uriLine); layout->addWidget(p_uriPushButton);
  layout->addWidget(p_colorLine); layout->addWidget(p_colorPushButton); layout->addWidget(p_ID1Label);
  layout->addWidget(p_ID1SpinBox); layout->addWidget(p_ID2Label); layout->addWidget(p_ID2SpinBox);
  layout->addWidget(p_rateLabel); layout->addWidget(p_rateSpinBox); layout->addWidget(p_opacityLabel);
  layout->addWidget(p_opacitySpinBox); layout->addWidget(p_volumeLabel); layout->addWidget(p_volumeSpinBox);
  layout->addWidget(m_nameLineEdit); layout->addWidget(m_nameLineEdit2); layout->addWidget(m_IDLabel);
  layout->addWidget(m_IDSpinBox); layout->addWidget(m_opacityLabel); layout->addWidget(m_opacitySpinBox);
  layout->addWidget(m_visibleCheckBox); layout->addWidget(m_soloCheckBox); layout->addWidget(m_lockCheckBox);
  layout->addWidget(m_depthLabel); layout->addWidget(m_depthSpinBox); layout->addWidget(fadeCheckBox);
  layout->addWidget(timeLabel); layout->addWidget(timeSpinBox); layout->addWidget(waitTimeLabel);
  layout->addWidget(waitTimeSpinBox);
  layout->addStretch();
  layout->addWidget(sendPushButton); layout->addWidget(addToCuePushButton);

  myToolBarWidget->setLayout(layout);

  myToolBar->addWidget(myToolBarWidget);

  // On cache tout et on montre suivant les besoins
  p_nameLineEdit->hide(); p_nameLineEdit2->hide(); p_uriLine->hide(); p_uriPushButton->hide();
  p_colorLine->hide(); p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide();
  p_ID2Label->hide(); p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide();
  p_opacityLabel->hide(); p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide();
  m_nameLineEdit->hide(); m_nameLineEdit2->hide(); m_IDLabel->hide(); m_IDSpinBox->hide();
  m_opacityLabel->hide(); m_opacitySpinBox->hide(); m_visibleCheckBox->hide(); m_soloCheckBox->hide();
  m_lockCheckBox->hide(); m_depthLabel->hide(); m_depthSpinBox->hide(); fadeCheckBox->hide();
  timeLabel->hide(); timeSpinBox->hide();

}

void MainWindow::createStatusBar()
{
  statusBar = new QStatusBar(this);
  progressBarCue = new QProgressBar(this);
  outputLabel = new QLabel(this);
  outputLabel->setAlignment(Qt::AlignRight);
  progressBarSend = new QProgressBar(this);
  QFile file(":/qss/BarSend");
      file.open(QFile::ReadOnly);
      QString styleSheet = QString::fromLatin1(file.readAll());
      progressBarSend->setStyleSheet(styleSheet);

  statusBar->insertPermanentWidget(0, progressBarCue, 1);
  statusBar->insertPermanentWidget(1, outputLabel, 1);
  statusBar->insertPermanentWidget(2, progressBarSend, 1);
  setStatusBar(statusBar);
  progressBarCue->setRange(0, 100);
}

void MainWindow::showWidgets(int index)
{
  switch (index)
  {
  case PLAY: case PAUSE: case REWIND: case QUIT:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_NAME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_REWIND:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_OPACITY:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->show();
    p_opacitySpinBox->show(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_VOLUME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->show(); p_volumeSpinBox->show(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_RATE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->show(); p_rateSpinBox->show(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_URI:
    p_uriLine->show(); p_uriPushButton->show(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0);
    p_uriLine->setText("Choose-->"); break;
  case P_COLOR:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->show();
    p_colorPushButton->show(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0);
    p_colorLine->setText("Choose-->"); break;
  case M_NAME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case M_OPACITY:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->show(); m_opacitySpinBox->show();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case M_VISIBLE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->show(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case M_SOLO:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->show(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case M_LOCK:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->show(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case M_DEPTH:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->show(); m_IDSpinBox->show(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->show();
    m_depthSpinBox->show(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case P_XFADE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->show();
    p_ID2SpinBox->show(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->show(); timeSpinBox->show(); timeSpinBox->setValue(2); waitTimeSpinBox->setValue(0); break;
  case P_FADE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->show(); p_ID1SpinBox->show(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->show(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->show(); timeSpinBox->show(); timeSpinBox->setValue(2); waitTimeSpinBox->setValue(0); break;
  case R_P_NAME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->show(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_REWIND:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_OPACITY:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->show();
    p_opacitySpinBox->show(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_VOLUME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->show(); p_volumeSpinBox->show(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_RATE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->show(); p_rateSpinBox->show(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_URI:
    p_uriLine->show(); p_uriPushButton->show(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0);
    p_uriLine->setText("Choose-->"); break;
  case R_P_COLOR:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->show();
    p_colorPushButton->show(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0);
    p_colorLine->setText("Choose-->"); break;
  case R_M_NAME:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->show();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_M_OPACITY:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->show(); m_opacitySpinBox->show();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_M_VISIBLE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->show(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_M_SOLO:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->show(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_M_LOCK:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->show(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_M_DEPTH:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->hide(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->show();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->show();
    m_depthSpinBox->show(); fadeCheckBox->hide(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->hide(); timeSpinBox->hide(); waitTimeSpinBox->setValue(0); break;
  case R_P_FADE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->show(); p_nameLineEdit2->hide(); m_nameLineEdit2->hide();
    timeLabel->show(); timeSpinBox->show(); timeSpinBox->setValue(2); waitTimeSpinBox->setValue(0); break;
  case R_P_XFADE:
    p_uriLine->hide(); p_uriPushButton->hide(); p_nameLineEdit->show(); p_colorLine->hide();
    p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide(); p_ID2Label->hide();
    p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide(); p_opacityLabel->hide();
    p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide(); m_nameLineEdit->hide();
    m_IDLabel->hide(); m_IDSpinBox->hide(); m_opacityLabel->hide(); m_opacitySpinBox->hide();
    m_visibleCheckBox->hide(); m_soloCheckBox->hide(); m_lockCheckBox->hide(); m_depthLabel->hide();
    m_depthSpinBox->hide(); fadeCheckBox->hide(); p_nameLineEdit2->show(); m_nameLineEdit2->hide();
    timeLabel->show(); timeSpinBox->show(); timeSpinBox->setValue(2); waitTimeSpinBox->setValue(0); break;
  default:
    p_nameLineEdit->hide(); p_nameLineEdit2->hide(); p_uriLine->hide(); p_uriPushButton->hide();
    p_colorLine->hide(); p_colorPushButton->hide(); p_ID1Label->hide(); p_ID1SpinBox->hide();
    p_ID2Label->hide(); p_ID2SpinBox->hide(); p_rateLabel->hide(); p_rateSpinBox->hide();
    p_opacityLabel->hide(); p_opacitySpinBox->hide(); p_volumeLabel->hide(); p_volumeSpinBox->hide();
    m_nameLineEdit->hide(); m_nameLineEdit2->hide(); m_IDLabel->hide(); m_IDSpinBox->hide();
    m_opacityLabel->hide(); m_opacitySpinBox->hide(); m_visibleCheckBox->hide(); m_soloCheckBox->hide();
    m_lockCheckBox->hide(); m_depthLabel->hide(); m_depthSpinBox->hide(); fadeCheckBox->hide(); break;
  }
}
void MainWindow::sendFromToolBar()
{
  champMM index = static_cast<champMM>(champComboBox->currentIndex());
  auto *oscsend = new OscSend(
        this,
        index,
        nullptr,
        p_uriLine->text(),
        p_nameLineEdit->text(),
        p_nameLineEdit2->text(),
        p_colorLine->text(),
        p_ID1SpinBox->value(),
        p_ID2SpinBox->value(),
        p_rateSpinBox->value(),
        p_opacitySpinBox->value(),
        p_volumeSpinBox->value(),
        m_nameLineEdit->text(),
        m_nameLineEdit2->text(),
        m_IDSpinBox->value(),
        m_opacitySpinBox->value(),
        m_visibleCheckBox->isChecked(),
        m_soloCheckBox->isChecked(),
        m_lockCheckBox->isChecked(),
        m_depthSpinBox->value(),
        timeSpinBox->value(),
        fadeCheckBox->isChecked(),
        waitTimeSpinBox->value()
        );
  switch(index){
  case P_URI: case R_P_URI: while (p_uriLine->text() == "Choose->") setP_UriLine(); oscsend->setP_uri(p_uriLine->text()); break;
  case P_COLOR: case R_P_COLOR: while (p_colorLine->text() == "Choose->") setP_ColorLine(); oscsend->setP_color(p_colorLine->text()); break;
  default: break;
  }
  connect(oscsend, SIGNAL(sendStringToOutputLabel(QString)), outputLabel, SLOT(setText(QString)));
  oscsend->ExecuteSend();
}
void MainWindow::setP_UriLine()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Choose File",
                                                  "",
                                                  "Media Files (*.png *.jpg *.gif *.tif *.mov *.avi *.mp4)");
  p_uriLine->setText(fileName);
}
void MainWindow::setP_ColorLine()
{
  QColor colorTemp = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
  p_colorLine->setText(colorTemp.name());
}
void MainWindow::addToCue()
{
  champMM champ = static_cast<champMM>(champComboBox->currentIndex());
  auto *oscsend = new OscSend(
        this,
        champ,
        nullptr,
        p_uriLine->text(),
        p_nameLineEdit->text(),
        p_nameLineEdit2->text(),
        p_colorLine->text(),
        p_ID1SpinBox->value(),
        p_ID2SpinBox->value(),
        p_rateSpinBox->value(),
        p_opacitySpinBox->value(),
        p_volumeSpinBox->value(),
        m_nameLineEdit->text(),
        m_nameLineEdit2->text(),
        m_IDSpinBox->value(),
        m_opacitySpinBox->value(),
        m_visibleCheckBox->isChecked(),
        m_soloCheckBox->isChecked(),
        m_lockCheckBox->isChecked(),
        m_depthSpinBox->value(),
        timeSpinBox->value(),
        fadeCheckBox->isChecked(),
        waitTimeSpinBox->value()
        );
  switch(champ){
  case P_URI: case R_P_URI: while (p_uriLine->text() == "Choose->") setP_UriLine(); oscsend->setP_uri(p_uriLine->text()); break;
  case P_COLOR: case R_P_COLOR: while (p_colorLine->text() == "Choose->") setP_ColorLine(); oscsend->setP_color(p_colorLine->text()); break;
  default: break;
  }
  QModelIndex index = tabseq->treeView->currentIndex();
  if (!index.isValid())
  {
    if (!oscCueList->rowCount()) // Si y a pas de cue on en crée une
    {
      oscCueList->addCue(); // On en crée une
      oscCueList->addSend(oscsend, 0); // on y ajoute le send
      tabseq->hideShowColumns();
      return;
    }
    oscCueList->addSend(oscsend, oscCueList->rowCount() - 1);
    tabseq->hideShowColumns();
    return;
  }
  // l'index est valide
  int row = tabseq->treeView->currentIndex().row();
  if (oscCueList->isCue(index)) // C'est une cue
  {
    oscCueList->addSend(oscsend, row);
    tabseq->hideShowColumns();
    return;
  }
  // c'est un send
  oscCueList->insertSend(oscsend, index.parent().row(), row); // Il ajoute avant le send...
  tabseq->hideShowColumns();
}

void MainWindow::timeProgressedCue(int value)
{
  if (value >= 0 && value <= 100) progressBarCue->setValue(value);
  return;
}

void MainWindow::timeFinishedCue()
{
  progressBarCue->reset();
}

void MainWindow::timeProgressedSend(int value)
{
  if (value >= 0 && value <= 100) progressBarSend->setValue(value);
  return;
}

void MainWindow::timeFinishedSend()
{
  progressBarSend->reset();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  QMessageBox msgBox(QMessageBox::Warning, "",
                     "WARNING, are you sure you want to quit ?", nullptr, this);
  msgBox.setWindowIcon(icon);
  msgBox.addButton("OK", QMessageBox::AcceptRole);
  msgBox.addButton("CANCEL", QMessageBox::RejectRole);
  if (msgBox.exec() == QMessageBox::RejectRole) event->ignore();
  else event->accept();
}
