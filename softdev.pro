TEMPLATE     = app
TARGET       = softdev
DEPENDPATH  += . src lib/libPF
INCLUDEPATH += . inc lib/libPF
DESTDIR      = bin
OBJECTS_DIR  = obj
MOC_DIR      = generated
RCC_DIR      = generated
RESOURCES   += resources/resources.qrc
QT          += core gui
LIBS        += -lstdc++fs
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# valgrind memchecking
QMAKE_CXXFLAGS += -g
QMAKE_CFLAGS += -g

HEADERS += \
           inc/functions.h \
           # Game objects
           inc/Game/GameObject.h \
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
           lib/libPF/PF.h \
           # QT Objects
           inc/UI/GameWindow.h \
           inc/UI/TitleScreen.h \
           inc/UI/Dialog.h
SOURCES += \
           src/main.cpp \
           src/functions.cpp \
           # Game Objects
           src/Game/GameObject.cpp \
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
           lib/libPF/PF_Format.c \
           lib/libPF/PF_ReadParameterFile.c \
           lib/libPF/PF_RPF_ExtractCommentlessLine.c \
           lib/libPF/PF_RPF_ReadArray.c \
           lib/libPF/PF_WriteParameters.c \
           lib/libPF/PF_FreeStringArray.c \
           # QT Objects
           src/UI/GameWindow.cpp \
           src/UI/TitleScreen.cpp \
           src/UI/Dialog.cpp

DISTFILES += \
             # Fonts
             resources/fonts/Roboto.ttf \
             resources/fonts/KronaOne.ttf