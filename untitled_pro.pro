QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FireBallBase.cpp \
    FireBallNomal.cpp \
    enemyBase.cpp \
    enemyZomble.cpp \
    enemyZombleFire.cpp \
    enemyZombleFireGiant.cpp \
    enemyZombleWind.cpp \
    fire.cpp \
    gameEngine.cpp \
    magicBase.cpp \
    magicFire.cpp \
    main.cpp \
    gameWidget.cpp \
    player.cpp \
    skillBase.cpp \
    startMenu.cpp

HEADERS += \
    FireBallBase.h \
    FireBallNomal.h \
    enemyBase.h \
    enemyZomble.h \
    enemyZombleFire.h \
    enemyZombleFireGiant.h \
    enemyZombleWind.h \
    fire.h \
    gameEngine.h \
    gameWidget.h \
    magicBase.h \
    magicFire.h \
    player.h \
    skillBase.h \
    startMenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
