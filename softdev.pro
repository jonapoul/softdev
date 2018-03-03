TEMPLATE     = app
TARGET       = softdev
DEPENDPATH  += . inc src lib/libpf
INCLUDEPATH += . inc lib/libpf
DESTDIR      = bin
OBJECTS_DIR  = obj
MOC_DIR      = generated
RCC_DIR      = generated
RESOURCES   += resources/resources.qrc
QT          += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
           # Game objects
           inc/Captain.h \
           inc/Die.h \
           inc/GameEngine.h \
           inc/Hierophant.h \
           inc/Parameters.h \
           inc/Player.h \
           inc/Skill.h \
           inc/SkillTree.h \
           inc/Squad.h \
           inc/SquadMember.h \
           inc/functions.h \
           # libPF parameter reading
           lib/libpf/PF.h \
           # QT Objects
           inc/GameWindow.h \
           inc/Dialog.h
SOURCES += \
           # Game Objects
           src/main.cpp \
           src/Captain.cpp \
           src/Die.cpp \
           src/GameEngine.cpp \
           src/Hierophant.cpp \
           src/Parameters.cpp \
           src/Player.cpp \
           src/Skill.cpp \
           src/SkillTree.cpp \
           src/Squad.cpp \
           src/SquadMember.cpp \
           src/functions.cpp \
           # libPF parameter reading
           lib/libpf/PF_Format.c \
           lib/libpf/PF_ReadParameterFile.c \
           lib/libpf/PF_RPF_ExtractCommentlessLine.c \
           lib/libpf/PF_RPF_ReadArray.c \
           lib/libpf/PF_WriteParameters.c \
           # QT Objects
           src/GameWindow.cpp \
           src/Dialog.cpp

DISTFILES += \
             resources/fonts/Roboto.ttf \
             resources/fonts/KronaOne.ttf