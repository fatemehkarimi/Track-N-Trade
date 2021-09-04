QT += core widgets gui
TEMPLATE = app
TARGET  = TrackNTrade

INCLUDEPATH += $$PWD/src

HEADERS += $$PWD/src/data/*.h
HEADERS += $$PWD/src/window/*.h
HEADERS += $$PWD/src/settings/*.h

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/src/data/*.cpp
SOURCES += $$PWD/src/window/*.cpp
SOURCES += $$PWD/src/settings/*.cpp
