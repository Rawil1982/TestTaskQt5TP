TEMPLATE = subdirs

SUBDIRS += \
    rawil_core \
    rawil_gui \
    rawil_app \
    rawil_tests

rawil_core.depends =
rawil_gui.depends = rawil_core
rawil_app.depends = rawil_core rawil_gui
rawil_tests.depends = rawil_core rawil_gui

CONFIG += c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
