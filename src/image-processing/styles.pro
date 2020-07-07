QT += widgets core

HEADERS       = norwegianwoodstyle.h \
                widgetgallery.h \
    UI/CFileTab.h \
    UI/CTextTab.h \
    UI/COutputTab.h \
    UI/CCustomizeTab.h \
    CMainTabDialog.h \
    global.h \
    UI/CMergeThread.h
SOURCES       = main.cpp \
                norwegianwoodstyle.cpp \
                widgetgallery.cpp \
    UI/CFileTab.cpp \
    UI/CTextTab.cpp \
    UI/COutputTab.cpp \
    UI/CCustomizeTab.cpp \
    CMainTabDialog.cpp \
    UI/CMergeThread.cpp
RESOURCES     = styles.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/styles
INSTALLS += target
