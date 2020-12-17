QT +=widgets

LIBS += -L/alsa/ -lasound\
    -lrtmidi\

#TARGET +=qtdebug
#TEMPLATE = app
#CONFIG += debug
CONFIG += console debug

INCLUDEPATH += \
    $$PWD/src \
    $$PWD/src/control \
    $$PWD/src/gui \
    $$PWD/contrib/oscpack/osc \
    $$PWD/contrib/oscpack/ip

SOURCES += \
    src/control/mmstatelist.cpp \
    src/control/mymidi.cpp \
    src/main.cpp \
    contrib/oscpack/osc/OscTypes.cpp \
    contrib/oscpack/osc/OscOutboundPacketStream.cpp \
    src/gui/mainwindow.cpp \
    src/gui/tabmidi.cpp \
    src/gui/tabseq.cpp \
    src/control/oscsend.cpp \
    src/control/osccuelist.cpp \
    src/control/mmstate.cpp \
    src/gui/tabmmstate.cpp

unix {
    SOURCES *= \
    contrib/oscpack/ip/posix/UdpSocket.cpp \
    contrib/oscpack/ip/posix/NetworkingUtils.cpp \
    contrib/oscpack/ip/IpEndpointName.cpp
    }


HEADERS += \
    src/MMC.h \
    src/control/mmstatelist.h \
    src/control/mymidi.h \
    src/gui/mainwindow.h \
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

