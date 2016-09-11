#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T17:18:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_LCM_WINDOWS
TEMPLATE = app

CONFIG += c++11
QMAKE_CFLAGS += -std=c99


contains(TEMPLATE, "lib"){
    DESTDIR =./lib
    DLLDESTDIR = ./bin
}else{
    DESTDIR = ./bin
}
UI_DIR = ./ui
OBJECTS_DIR = ./obj
MOC_DIR = ./moc

SOURCES += main.cpp\
        mainwindow.cpp \
    lcm/lcm.c \
    lcm/lcm_file.c \
    lcm/lcm_memq.c \
    lcm/lcm_mpudpm.c \
    lcm/lcm_tcpq.c \
    lcm/lcm_udpm.c \
    lcm/ringbuffer.c \
    lcm/udpm_util.c \
    lcm/eventlog.c \
    lcm/windows/WinLCM.cpp \
    lcm/windows/WinPorting.cpp \
    lcm/lcmtypes/channel_port_map_update_t.c \
    lcm/lcmtypes/channel_to_port_t.c


HEADERS  += mainwindow.h \
    include/action_feedback_t.hpp \
    include/angle_speed_t.hpp \
    include/battery_status_t.hpp \
    include/cmd_vel_t.hpp \
    include/joy_t.hpp \
    include/lidar_laser_t.hpp \
    include/linear_speed_t.hpp \
    include/map_t.hpp \
    include/mask_list_t.hpp \
    include/mask_t.hpp \
    include/mode_t.hpp \
    include/odom_t.hpp \
    include/path_list_t.hpp \
    include/path_t.hpp \
    include/pose_t.hpp \
    include/pose_xyt_t.hpp \
    include/sensor_data_t.hpp \
    include/speech_t.hpp \
    include/task_list_t.hpp \
    include/task_t.hpp \
    include/waypoint_list_t.hpp \
    include/waypoint_t.hpp \
    lcm/dbg.h \
    lcm/ioutils.h \
    lcm/lcm-cpp-impl.hpp \
    lcm/lcm-cpp.hpp \
    lcm/lcm.h \
    lcm/lcm_coretypes.h \
    lcm/lcm_internal.h \
    lcm/ringbuffer.h \
    lcm/udpm_util.h \
    lcm/eventlog.h \
    lcm/windows/WinPorting.h

FORMS    += mainwindow.ui

DISTFILES += \
    glib-2.0/lib-2.0.pri

win32 {
    # windows only
    DEPENDPATH += $$PWD/lcm/lcmtypes
    INCLUDEPATH += $$PWD/lcm/lcmtypes
    INCLUDEPATH += $$PWD/glib-2.0
    INCLUDEPATH += $$PWD/lcm/glib-2.0/gobject
    INCLUDEPATH += $$PWD/glib-2.0/gio
    INCLUDEPATH += $$PWD/lcm/glib-2.0glib
    INCLUDEPATH += $$PWD/lib/glib-2.0/include


     LIBS += -lws2_32

     LIBS += -L$$PWD/lib/ -lgobject-2.0.dll \
                          -lglib-2.0.dll \
                          -lgio-2.0.dll \
                          -lgthread-2.0.dll
#     LIBS += $$PWD/lib/gobject-2.0.lib \
#                       glib-2.0.lib \
#                       gio-2.0.lib \
#                       gthread-2.0.lib





}
