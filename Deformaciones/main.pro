######################################################################
# Automatically generated by qmake (1.07a) Wed Oct 6 11:42:48 2004
######################################################################

TEMPLATE = app
TARGET		= deformaciones
INCLUDEPATH += .
# ¿Es necesario incluir este camino? :
#INCLUDEPATH += "/usr/X11/include"


QT += opengl

# Input
HEADERS += painter.h canvas.h ./figuras/*.h ./utils/*.h
SOURCES += main.cpp painter.cpp canvas.cpp ./figuras/*.cpp ./utils/*.cpp
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -lglut -lGLU -lGL