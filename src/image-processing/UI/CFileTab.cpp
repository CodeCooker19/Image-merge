#include "CFileTab.h"
#include "../global.h"
#include <QGroupBox>
#include <QLayout>

static void findRecursion(const QString &path, const QList<QString> &pattern, QStringList *result)
{
    QDir currentDir(path);
    const QString prefix = path + QLatin1Char('\\');
    foreach (const QString &match, currentDir.entryList(pattern, QDir::Files | QDir::NoSymLinks))
        result->append(prefix + match);
    foreach (const QString &dir, currentDir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot))
        findRecursion(prefix + dir, pattern, result);
}

//public
CFileTab::CFileTab(QWidget *parent) : QWidget(parent)
{
    initUI();

    connect(m_pAddImageBtn, SIGNAL(clicked(bool)), this, SLOT(onAddImageClickded()));
    connect(m_pAddFolderBtn, SIGNAL(clicked(bool)), this, SLOT(onAddFolderClickded()));
    connect(m_pRemoveFileBtn, SIGNAL(clicked(bool)), this, SLOT(onRemoveFileClickded()));
    connect(m_pClearFileBtn, SIGNAL(clicked(bool)), this, SLOT(onClearFileClickded()));
    connect(m_pAddExtBtn, SIGNAL(clicked(bool)), this, SLOT(onAddExtClickded()));
    connect(m_pRemoveExtBtn, SIGNAL(clicked(bool)), this, SLOT(onRemoveExtClickded()));
    connect(m_pClearExtBtn, SIGNAL(clicked(bool)), this, SLOT(onClearExtClickded()));
    connect(m_pFileListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onFileSelectionChangeded()));
}

QList<QString> CFileTab::getImagePaths(){

}

//private:
void CFileTab::initUI(){
    QVBoxLayout *pMainLayout = new QVBoxLayout(this);

    QFont font = this->font();
    font.setPixelSize(FONT_SIZE * 0.7);

    //File Image
    QGroupBox *pImageGroupBox = new QGroupBox(tr("File Imge"));
    m_pAddImageBtn = new QPushButton(tr("Add Images"));
    m_pAddImageBtn->setDefault(true);

    m_pAddFolderBtn = new QPushButton(tr("Add Folder"));
    m_pAddFolderBtn->setDefault(true);

    m_pRemoveFileBtn = new QPushButton(tr("Remove Selected"));
    m_pRemoveFileBtn->setDefault(true);

    m_pClearFileBtn = new QPushButton(tr("Clear All Files"));
    m_pClearFileBtn->setDefault(true);

    m_pImportLabel = new QLabel(STR_BASE_FILES);
    m_pSelectLabel = new QLabel(STR_FILE_SELECTED);
    m_pFileListWidget = new QListWidget(this);
    m_pFileListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    m_pFileListWidget->setFixedSize(g_sizeDLG.width() * 0.7, g_sizeDLG.height() * 0.5);
    m_pFileListWidget->setFont(font);

    QVBoxLayout *pBtnLayout = new QVBoxLayout(this);
    pBtnLayout->addWidget(m_pAddImageBtn);
    pBtnLayout->addWidget(m_pAddFolderBtn);
    pBtnLayout->addWidget(m_pRemoveFileBtn);
    pBtnLayout->addWidget(m_pClearFileBtn);

    QHBoxLayout *pLabelLayout = new QHBoxLayout(this);
    pLabelLayout->addWidget(m_pImportLabel);
    pLabelLayout->addWidget(m_pSelectLabel);

    QVBoxLayout *pListLayout = new QVBoxLayout(this);
    pListLayout->addLayout(pLabelLayout);
    pListLayout->addWidget(m_pFileListWidget);

    QHBoxLayout *pFileLayout = new QHBoxLayout(this);
    pFileLayout->addLayout(pBtnLayout);
    pFileLayout->addLayout(pListLayout);

    pImageGroupBox->setLayout(pFileLayout);

    //File extensions
    QGroupBox *pExGroupBox = new QGroupBox(tr("File Extensions"));

    m_pAddExtBtn = new QPushButton(tr("Add Extension"));
    m_pAddExtBtn->setDefault(true);

    m_pRemoveExtBtn = new QPushButton(tr("Remove Selected Extension"));
    m_pRemoveExtBtn->setDefault(true);

    m_pClearExtBtn = new QPushButton(tr("Remove All Extensions"));
    m_pClearExtBtn->setDefault(true);

    QLabel *pFileTypeLabel = new QLabel(STR_FILE_TYPE);
    m_pExtLineEdit = new QLineEdit(this);
    m_pExtListWidget = new QListWidget(this);
    m_pExtListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    m_pExtListWidget->setFixedWidth(g_sizeDLG.width()/5);
    pFileTypeLabel->setFixedWidth(g_sizeDLG.width()/5);
    m_pExtLineEdit->setFixedWidth(g_sizeDLG.width()/5);

    QStringList listExt;
    listExt << ".png" << ".jpeg" << ".jpg" << ".gif" << ".bmp";
    m_pExtListWidget->addItems(listExt);

    QVBoxLayout *pExBtnLayout = new QVBoxLayout(this);
    pExBtnLayout->addWidget(m_pAddExtBtn);
    pExBtnLayout->addWidget(m_pRemoveExtBtn);
    pExBtnLayout->addWidget(m_pClearExtBtn);

    QVBoxLayout *pFileTypeLayout = new QVBoxLayout(this);
    pFileTypeLayout->addStretch();
    pFileTypeLayout->addWidget(pFileTypeLabel);
    pFileTypeLayout->addSpacing(g_sizeDLG.height()/90);
    pFileTypeLayout->addWidget(m_pExtLineEdit);
    pFileTypeLayout->addStretch();

    QHBoxLayout *pExMainLayout = new QHBoxLayout(this);
    pExMainLayout->addLayout(pExBtnLayout);
    pExMainLayout->addLayout(pFileTypeLayout);
    pExMainLayout->addWidget(m_pExtListWidget);

    pExGroupBox->setLayout(pExMainLayout);

    pMainLayout->addWidget(pImageGroupBox);
    pMainLayout->addWidget(pExGroupBox);
    setLayout(pMainLayout);
}

void CFileTab::showImportFileCount(){

}
//private slots:
void CFileTab::onAddImageClickded(){

}

void CFileTab::onAddFolderClickded(){

}

void CFileTab::onRemoveFileClickded(){

}

void CFileTab::onClearFileClickded(){

}

void CFileTab::onAddExtClickded(){

}

void CFileTab::onRemoveExtClickded(){

}

void CFileTab::onClearExtClickded(){

}

void CFileTab::onFileSelectionChangeded(){

}
