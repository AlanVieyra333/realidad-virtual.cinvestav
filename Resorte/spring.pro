######################################################################
# Automatically generated by qmake (1.07a) Wed Oct 6 11:42:48 2004
######################################################################

TEMPLATE = app
TARGET		= spring
INCLUDEPATH += .
INCLUDEPATH += "/usr/X11/include"
INCLUDEPATH += "/Library/Frameworks"

QT += opengl

# Input
HEADERS += painter.h spring.h
SOURCES += main.cpp painter.cpp spring.cpp

LIBS += -F/Library/Frameworks -framework 3DconnexionClient