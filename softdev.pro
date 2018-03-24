TEMPLATE       = app
TARGET         = softdev_qt
DEPENDPATH    += . src lib/libpf
INCLUDEPATH   += . inc lib/libpf
DESTDIR        = bin
OBJECTS_DIR    = obj
MOC_DIR        = generated
RCC_DIR        = generated
RESOURCES     += resources/resources.qrc
QT            += core gui
LIBS          += -lstdc++fs
QMAKE_MAKEFILE = Qt_Makefile
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# valgrind memchecking
QMAKE_CXXFLAGS += -g
QMAKE_CFLAGS += -g

HEADERS += \
           config.h \
           inc/Global.h \
           # Game objects
           inc/Game/GameObject.h \
           inc/Game/Captain.h \
           inc/Game/Die.h \
           inc/Game/GameEngine.h \
           inc/Game/Hierophant.h \
           inc/Game/Item.h \
           inc/Game/GameParameters.h \
           inc/Game/Player.h \
           inc/Game/Skill.h \
           inc/Game/SkillTree.h \
           inc/Game/SpecialisedSquadMember.h \
           inc/Game/Squad.h \
           inc/Game/SquadMember.h \
           inc/Game/StatBoost.h \
           inc/Game/Weapon.h \
           # libpf parameter reading
           lib/libpf/PF.h \
           # QT Objects
           inc/UI/GameWindow.h \
           inc/UI/TitleScreen.h \
           inc/UI/Dialog.h
SOURCES += \
           src/main.cpp \
           src/Global.cpp \
           # Game Objects
           src/GameObject.cpp \
           src/Captain.cpp \
           src/Die.cpp \
           src/GameEngine.cpp \
           src/Hierophant.cpp \
           src/Item.cpp \
           src/GameParameters.cpp \
           src/Player.cpp \
           src/Skill.cpp \
           src/SkillTree.cpp \
           src/SpecialisedSquadMember.cpp \
           src/Squad.cpp \
           src/SquadMember.cpp \
           src/StatBoost.cpp \
           src/Weapon.cpp \
           # libpf parameter reading
           lib/libpf/PF_Format.c \
           lib/libpf/PF_ReadParameterFile.c \
           lib/libpf/PF_RPF_ExtractCommentlessLine.c \
           lib/libpf/PF_RPF_ReadArray.c \
           lib/libpf/PF_WriteParameters.c \
           lib/libpf/PF_FreeStringArray.c \
           # QT Objects
           src/GameWindow.cpp \
           src/TitleScreen.cpp \
           src/Dialog.cpp

DISTFILES += \
             # Fonts
             resources/fonts/Roboto.ttf \
             resources/fonts/KronaOne.ttf