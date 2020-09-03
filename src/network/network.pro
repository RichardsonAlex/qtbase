TARGET   = QtNetwork
QT = core-private

DEFINES += QT_NO_USING_NAMESPACE QT_NO_FOREACH
#DEFINES += QLOCALSERVER_DEBUG QLOCALSOCKET_DEBUG
#DEFINES += QNETWORKDISKCACHE_DEBUG
#DEFINES += QSSLSOCKET_DEBUG
#DEFINES += QHOSTINFO_DEBUG
#DEFINES += QABSTRACTSOCKET_DEBUG QNATIVESOCKETENGINE_DEBUG
#DEFINES += QTCPSOCKETENGINE_DEBUG QTCPSOCKET_DEBUG QTCPSERVER_DEBUG QSSLSOCKET_DEBUG
#DEFINES += QUDPSOCKET_DEBUG QUDPSERVER_DEBUG
#DEFINES += QSCTPSOCKET_DEBUG QSCTPSERVER_DEBUG
msvc:equals(QT_ARCH, i386): QMAKE_LFLAGS += /BASE:0x64000000

QMAKE_DOCS = $$PWD/doc/qtnetwork.qdocconf

MODULE_PLUGIN_TYPES = \
    networkaccessbackends

include(access/access.pri)
include(kernel/kernel.pri)
include(socket/socket.pri)
include(ssl/ssl.pri)

QMAKE_LIBS += $$QMAKE_LIBS_NETWORK

load(qt_module)
