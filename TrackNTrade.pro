QT += core widgets gui network concurrent
TEMPLATE = app
TARGET  = TrackNTrade

INCLUDEPATH += $$PWD/src

HEADERS += $$PWD/src/data/*.h
HEADERS += $$PWD/src/window/*.h
HEADERS += $$PWD/src/settings/*.h
HEADERS += $$PWD/src/network/*.h
HEADERS += $$PWD/src/components/table_market/*.h
HEADERS += $$PWD/src/components/search_box/*.h

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/src/data/*.cpp
SOURCES += $$PWD/src/window/*.cpp
SOURCES += $$PWD/src/settings/*.cpp
SOURCES += $$PWD/src/network/*.cpp
SOURCES += $$PWD/src/components/table_market/*.cpp
SOURCES += $$PWD/src/components/search_box/*.cpp

RESOURCES += \
        resources.qrc