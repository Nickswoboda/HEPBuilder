QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/exercise.cpp \
    src/exercise_layout.cpp \
    src/routine_layout.cpp \
    src/tooltip.cpp \
    src/preview_window.cpp \
    src/exercise_card.cpp \
    src/print_card.cpp \
    src/save_routine_window.cpp \
    src/load_routine_window.cpp \
    src/add_exercise_window.cpp \
    src/add_tags_window.cpp \
    src/tag_search_area.cpp

HEADERS += \
    src/mainwindow.h \
    src/exercise.h \
    src/exercise_layout.h \
    src/routine_layout.h \
    src/tooltip.h \
    src/preview_window.h \
    src/exercise_card.h \
    src/print_card.h \
    src/save_routine_window.h \
    src/load_routine_window.h \
    src/add_exercise_window.h \
    src/add_tags_window.h \
    src/tag_search_area.h

FORMS += \
    src/mainwindow.ui \
    src/previewwindow.ui \
    src/exercisecard.ui \
    src/printcard.ui \
    src/saveroutinewindow.ui \
    src/loadroutinewindow.ui \
    src/addexercisewindow.ui \
    src/addtagswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
