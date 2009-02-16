# -------------------------------------------------
# Project created by QtCreator 2009-02-16T12:40:55
# -------------------------------------------------
QT += svg \
    webkit
TARGET = biocheat
TEMPLATE = app
SOURCES += main.cpp \
    Window.cpp \
    Capture.cpp \
    Recognizer.cpp \
    SimpleHinter.cpp \
    Visualizer.cpp
HEADERS += Window.h \
    Capture.h \
    Recognizer.h \
    SimpleHinter.h \
    Visualizer.h
FORMS += Window.ui
RESOURCES += data/data.qrc
