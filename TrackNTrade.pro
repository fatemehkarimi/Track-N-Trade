QT += core widgets gui network
TEMPLATE = app
TARGET  = TrackNTrade

INCLUDEPATH += $$PWD/src

HEADERS += $$PWD/src/data/*.h
HEADERS += $$PWD/src/window/*.h
HEADERS += $$PWD/src/settings/*.h
HEADERS += $$PWD/src/network/*.h

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/src/data/*.cpp
SOURCES += $$PWD/src/window/*.cpp
SOURCES += $$PWD/src/settings/*.cpp
SOURCES += $$PWD/src/network/*.cpp
