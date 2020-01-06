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
    mainwindow.h \
    mymidiin.h \
    tabmidi.h \
    tabseq.h \
    oscsend.h \
    osccuelist.h \
    mmstate.h \
    tabmmstate.h

DISTFILES += \
    LICENSE.md \
    README.md \
    notes.txt

RESOURCES += \
  resources/resources.qrc
