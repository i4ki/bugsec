# -------------------------------------------------
# Project created by QtCreator 2010-02-12T19:25:33
# -------------------------------------------------
QWT_ROOT = /home/bpasti/programacao/qwt-5.2
include( $${QWT_ROOT}/qwtconfig.pri )
SUFFIX_STR = 
VVERSION = $$[QT_VERSION]
isEmpty(VVERSION) { 
    # Qt 3
    debug:SUFFIX_STR = $${DEBUG_SUFFIX}
    else:SUFFIX_STR = $${RELEASE_SUFFIX}
}
else { 
    CONFIG(debug, debug|release):SUFFIX_STR = $${DEBUG_SUFFIX}
    else:SUFFIX_STR = $${RELEASE_SUFFIX}
}
MOC_DIR = moc
INCLUDEPATH += $${QWT_ROOT}/src \
    /opt/qt-everywhere-opensource-src-4.6.2/plugins/imageformats
DEPENDPATH += $${QWT_ROOT}/src
OBJECTS_DIR = obj$${SUFFIX_STR}
TARGET = SquareRoot
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    wizard.cpp \
    wizardpages.cpp \
    algorithm/point.cpp \
    algorithm/curve.cpp \
    algorithm/minimosquadrados.cpp \
    polinomial.cpp \
    plot.cpp \
    plotcurve.cpp \
    actioncurve.cpp \
    about.cpp
HEADERS += mainwindow.h \
    wizard.h \
    wizardpages.h \
    algorithm/point.h \
    algorithm/curve.h \
    simple.h \
    algorithm/minimosquadrados.h \
    polinomial.h \
    plot.h \
    plotcurve.h \
    actioncurve.h \
    about.h
RESOURCES += images.qrc
FORMS += about.ui
QWTLIB = qwt$${SUFFIX_STR}
win32 { 
    contains(CONFIG, QwtDll) { 
        DEFINES += QT_DLL \
            QWT_DLL
        QWTLIB = $${QWTLIB}$${VER_MAJ}
    }
    win32-msvc:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc.net:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2002:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2003:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2005:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2008:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-g++:LIBS += -L$${QWT_ROOT}/lib \
        -l$${QWTLIB}
}
else:LIBS += -L$${QWT_ROOT}/lib \
    -l$${QWTLIB}

OTHER_FILES += \
    INSTALL.txt
