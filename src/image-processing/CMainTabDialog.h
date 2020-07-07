#ifndef CMAINTABDIALOG_H
#define CMAINTABDIALOG_H

#include <QDialog>
#include <QTabWidget>

#include "UI/CCustomizeTab.h"
#include "UI/CFileTab.h"
#include "UI/COutputTab.h"
#include "UI/CTextTab.h"

class CMainTabDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CMainTabDialog(QWidget *parent = nullptr);
    CFileTab*       getFileWidget(){return m_pFileWidget;}
    CTextTab*       getTextWidget(){return m_pTextWidget;}
    CCustomizeTab*  getCustomWidget(){return m_pCustomizeWidget;}
    COutputTab*     getOutputWidget(){return m_pOutputWidget;}

private:
    void initUI();

private:
    QTabWidget      *m_pMainTabWidget;
    CFileTab        *m_pFileWidget;
    CTextTab        *m_pTextWidget;
    CCustomizeTab   *m_pCustomizeWidget;
    COutputTab      *m_pOutputWidget;

signals:

public slots:
};

#endif // CMAINTABDIALOG_H
