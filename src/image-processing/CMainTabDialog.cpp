#include "CMainTabDialog.h"
#include "global.h"
#include "norwegianwoodstyle.h"
#include <QLayout>
#include <QApplication>

CMainTabDialog::CMainTabDialog(QWidget *parent) : QDialog(parent)
{
    initUI();
    QFont font = this->font();
    font.setPixelSize(FONT_SIZE);
    setFont(font);
    QApplication::setStyle(new NorwegianWoodStyle);
}

//private:
void CMainTabDialog::initUI(){
    m_pMainTabWidget = new QTabWidget(this);
    m_pFileWidget = new CFileTab(this);
    m_pTextWidget = new CTextTab(this);
    m_pCustomizeWidget = new CCustomizeTab(this);
    m_pOutputWidget = new COutputTab(this);

    m_pMainTabWidget->setFixedSize(g_sizeDLG);

    m_pMainTabWidget->addTab(m_pFileWidget, tr("File"));
    m_pMainTabWidget->addTab(m_pTextWidget, tr("Text"));
    m_pMainTabWidget->addTab(m_pCustomizeWidget, tr("Custom"));
    m_pMainTabWidget->addTab(m_pOutputWidget, tr("Output"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pMainTabWidget);
    setLayout(mainLayout);
    setWindowTitle(tr("Image Merge Dialog(Steve M.)"));
}
