QT += core widgets charts gui network concurrent
TEMPLATE = app
TARGET  = TrackNTrade

INCLUDEPATH += $$PWD/src

HEADERS += $$PWD/src/data/*.h
HEADERS += $$PWD/src/window/*.h
HEADERS += $$PWD/src/settings/*.h
HEADERS += $$PWD/src/network/*.h
HEADERS += $$PWD/src/components/search_box/*.h
HEADERS += $$PWD/src/components/tables/table_market/*.h
HEADERS += $$PWD/src/components/tables/table_price/*.h
HEADERS += $$PWD/src/components/tables/table_delegates/*.h
HEADERS += $$PWD/src/components/charts/*.h
HEADERS += $$PWD/src/components/charts/candlestick/*.h

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/src/data/*.cpp
SOURCES += $$PWD/src/window/*.cpp
SOURCES += $$PWD/src/settings/*.cpp
SOURCES += $$PWD/src/network/*.cpp
SOURCES += $$PWD/src/components/search_box/*.cpp
SOURCES += $$PWD/src/components/tables/table_market/*.cpp
SOURCES += $$PWD/src/components/tables/table_price/*.cpp
SOURCES += $$PWD/src/components/tables/table_delegates/*.cpp
SOURCES += $$PWD/src/components/charts/candlestick/*.cpp

RESOURCES += \
        resources.qrc
