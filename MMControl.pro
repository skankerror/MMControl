QT +=widgets

LIBS += -L/alsa/ -lasound\
    -lrtmidi\

#TARGET +=qtdebug
#TEMPLATE = app
#CONFIG += debug
#CONFIG += console debug

INCLUDEPATH += \
    $$PWD/src \
    $$PWD/src/control \
    $$PWD/src/gui \
    $$PWD/contrib/oscpack/osc \
    $$PWD/contrib/oscpack/ip

SOURCES += \
    src/control/mymidi.cpp \
    src/control/osccue.cpp \
    src/gui/osccuelistdelegate.cpp \
    src/main.cpp \
    contrib/oscpack/osc/OscTypes.cpp \
    contrib/oscpack/osc/OscOutboundPacketStream.cpp \
    contrib/oscpack/ip/UdpSocket.cpp \
    contrib/oscpack/ip/NetworkingUtils.cpp \
    contrib/oscpack/ip/IpEndpointName.cpp \
    src/gui/mainwindow.cpp \
    src/gui/tableview.cpp \
    src/gui/tabmidi.cpp \
    src/gui/tabseq.cpp \
    src/control/oscsend.cpp \
    src/control/osccuelist.cpp \
    src/control/mmstate.cpp \
    src/gui/tabmmstate.cpp

HEADERS += \
    src/MMC.h \
    src/control/mymidi.h \
    src/control/osccue.h \
    src/gui/mainwindow.h \
    src/gui/osccuelistdelegate.h \
    src/gui/tableview.h \
    src/gui/tabmidi.h \
    src/gui/tabseq.h \
    src/control/oscsend.h \
    src/control/osccuelist.h \
    src/control/mmstate.h \
    src/gui/tabmmstate.h


DISTFILES += \
    BUGS \
    LICENSE.md \
    README.md \
    TODO

RESOURCES += \
    resources/resources.qrc

