TEMPLATE     = app
TARGET       = softdev
DEPENDPATH  += . src lib/libpf
INCLUDEPATH += . inc lib/libpf
DESTDIR      = bin
OBJECTS_DIR  = obj
MOC_DIR      = generated
RCC_DIR      = generated
RESOURCES   += resources/resources.qrc
QT          += core gui
LIBS        += -lstdc++fs
QMAKE_CXXFLAGS += -g
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
           inc/functions.h \
           # Game objects
           inc/Game/Captain.h \
           inc/Game/Die.h \
           inc/Game/GameEngine.h \
           inc/Game/Hierophant.h \
           inc/Game/GameParameters.h \
           inc/Game/Player.h \
           inc/Game/Skill.h \
           inc/Game/SkillTree.h \
           inc/Game/Squad.h \
           inc/Game/SquadMember.h \
           # libPF parameter reading
           lib/libpf/PF.h \
           # QT Objects
           inc/UI/GameWindow.h \
           inc/UI/TitleScreen.h \
           inc/UI/Dialog.h
SOURCES += \
           src/main.cpp \
           src/functions.cpp \
           # Game Objects
           src/Game/Captain.cpp \
           src/Game/Die.cpp \
           src/Game/GameEngine.cpp \
           src/Game/Hierophant.cpp \
           src/Game/GameParameters.cpp \
           src/Game/Player.cpp \
           src/Game/Skill.cpp \
           src/Game/SkillTree.cpp \
           src/Game/Squad.cpp \
           src/Game/SquadMember.cpp \
           # libPF parameter reading
           lib/libpf/PF_Format.c \
           lib/libpf/PF_ReadParameterFile.c \
           lib/libpf/PF_RPF_ExtractCommentlessLine.c \
           lib/libpf/PF_RPF_ReadArray.c \
           lib/libpf/PF_WriteParameters.c \
           # QT Objects
           src/UI/GameWindow.cpp \
           src/UI/TitleScreen.cpp \
           src/UI/Dialog.cpp

DISTFILES += \
             # Fonts
             resources/fonts/Roboto.ttf \
             resources/fonts/KronaOne.ttf