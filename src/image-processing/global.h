#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSize>
#include <QString>
#include <QFont>
#include <QColor>
#include <QString>

class CMainTabDialog;
extern CMainTabDialog *g_pMainDlg;

enum TEXT_AREA{
    NONE_AREA = 0,
    TOP,
    MIDDLE,
    BOTTOM
};

enum TEXT_OVERLAY{
    NONE_OVERLAY = 0,
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

struct TEXT_INFO{
    bool            m_bIsArea;
    TEXT_AREA       m_nAreaPos;
    TEXT_OVERLAY    m_nOverlayPos;
    QList<QString>  m_listText;
};

struct CUSTOM_INFO{
    QFont       m_font;
    QColor      m_colorFont;
    QColor      m_colorBack;
    int         m_nOpacity;
};


struct OUTPUT_INFO
{
    QString     m_strOutputPath;
    QString     m_strKeyword;
    int         m_nCount;
    int         m_nTemplate;
};

#define FONT_SIZE 20
#define PANEL_SIZE 550
#define INTERVAL_SIZE 10
#define TEMPLATE_NUM 6
#define MAX_NUM 300000

const QSize g_sizeDLG(1024, 786);
const QSize g_sizePhoto(2000, 1980);

const QString STR_BASE_FILES(" base files");
const QString STR_FILE_SELECTED(" files selected");
const QString STR_FILE_TYPE("files type : ");
const QString STR_OPACITY("Opacity : ");

const int g_ImageCount[] = {1, 2, 2, 4, 3, 5};
#endif // GLOBAL_H
