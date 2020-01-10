QT +=widgets

LIBS += -L/alsa/ -lasound\
    -lrtmidi\


SOURCES += \
    main.cpp \
    contrib/oscpack/osc/OscTypes.cpp \
    contrib/oscpack/osc/OscOutboundPacketStream.cpp \
    contrib/oscpack/ip/UdpSocket.cpp \
    contrib/oscpack/ip/NetworkingUtils.cpp \
    contrib/oscpack/ip/IpEndpointName.cpp \
    mainwindow.cpp \
    mymidiin.cpp \
    tabmidi.cpp \
    tabseq.cpp \
    oscsend.cpp \
    osccuelist.cpp \
    mmstate.cpp \
    tabmmstate.cpp

HEADERS += \
    MMC.h \
    mainwindow.h \
    mymidiin.h \
    tabmidi.h \
    tabseq.h \
    oscsend.h \
    osccuelist.h \
    mmstate.h \
    tabmmstate.h

DISTFILES += \
    BUGS \
    LICENSE.md \
    README.md \
    TODO

RESOURCES += \
  resources/resources.qrc
