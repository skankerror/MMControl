QT +=widgets

LIBS += -L/alsa/ -lasound\
    -lrtmidi\


SOURCES += \
    main.cpp \
    oscpack/osc/OscTypes.cpp \
    oscpack/osc/OscOutboundPacketStream.cpp \
    oscpack/ip/UdpSocket.cpp \
    oscpack/ip/NetworkingUtils.cpp \
    oscpack/ip/IpEndpointName.cpp \
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
    notes.txt
