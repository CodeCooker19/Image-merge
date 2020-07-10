#include "CTextTab.h"
#include "../global.h"
#include <QGroupBox>
#include <QLayout>

CTextTab::CTextTab(QWidget *parent) : QWidget(parent)
{
    initUI();
    m_pAreaRadioBtn->setChecked(true);
    connect(m_pAddTextBtn, SIGNAL(clicked(bool)), this, SLOT(onAddTextClicked()));
    connect(m_pRemoveBtn, SIGNAL(clicked(bool)), this, SLOT(onRemoveClicked()));
    connect(m_pClearBtn, SIGNAL(clicked(bool)), this, SLOT(onClearClicked()));
    connect(m_pAddCSVBtn, SIGNAL(clicked(bool)), this, SLOT(onAddCSVClicked()));
    connect(m_pAddTXTBtn, SIGNAL(clicked(bool)), this, SLOT(onAddTXTClicked()));
}

TEXT_INFO CTextTab::getTextInfo(){
    TEXT_INFO info;
    info.m_bIsArea = m_pAreaRadioBtn->isChecked();
    info.m_nAreaPos = (TEXT_AREA)m_pAreaCombo->currentIndex();
    info.m_nOverlayPos = (TEXT_OVERLAY)m_pOverlayCombo->currentIndex();
    for(int i=0; i<m_pTextList->count(); i++){
        info.m_listText.append(m_pTextList->item(i)->text());
    }
    return info;
}

//private:
void CTextTab::initUI(){
    QVBoxLayout *pMainLayout = new QVBoxLayout(this);

    //Select TextType and Area Position
    QGroupBox *pTypeGroupBox = new QGroupBox(tr("Text Type & Area Position"));

    m_pAreaRadioBtn = new QRadioButton(tr("Text Area"));
    QLabel *pAreaLabel = new QLabel(tr("Text Area Position : "));
    m_pAreaCombo = new QComboBox(this);
    QStringList listArea;
    listArea << "None" << "Top" << "Middle"<< "Bottom";
    m_pAreaCombo->addItems(listArea);

    m_pOverlayRadioBtn = new QRadioButton(tr("Text Overlay"));
    QLabel *pOverlayLabel = new QLabel(tr("Text Overlay Position : "));
    m_pOverlayCombo = new QComboBox(this);
    QStringList listOverlay;
    listOverlay << "None" << "Top Left" << "Top Center" << "Top Right" << "Middle Left" << "Middle Center" << "Middle Right" << "Bottom Left" << "Bottom Center" << "Bottom Right";
    m_pOverlayCombo->addItems(listOverlay);

    QHBoxLayout *pAreaLayout = new QHBoxLayout(this);
    pAreaLayout->addWidget(m_pAreaRadioBtn);
    pAreaLayout->addWidget(pAreaLabel);
    pAreaLayout->addWidget(m_pAreaCombo);
    //pAreaLayout->addStretch();

    QHBoxLayout *pOverlayLayout = new QHBoxLayout(this);
    pOverlayLayout->addWidget(m_pOverlayRadioBtn);
    pOverlayLayout->addWidget(pOverlayLabel);
    pOverlayLayout->addWidget(m_pOverlayCombo);
    //pOverlayLayout->addStretch();

    QVBoxLayout *pTypeLayout = new QVBoxLayout(this);
    pTypeLayout->addLayout(pAreaLayout);
    pTypeLayout->addLayout(pOverlayLayout);

    pTypeGroupBox->setLayout(pTypeLayout);

    //Spining Text
    QGroupBox *pSpinGroupBox = new QGroupBox(tr("Spinnig Text"));

    m_pSpinEdit = new QLineEdit(this);
    m_pSpinEdit->setPlaceholderText(tr("Input text here..."));

    m_pAddTextBtn = new QPushButton(tr("Add Text"));
    m_pAddTextBtn->setDefault(true);

    m_pRemoveBtn = new QPushButton(tr("Remove"));
    m_pRemoveBtn->setDefault(true);

    m_pClearBtn = new QPushButton(tr("Remove All"));
    m_pClearBtn->setDefault(true);

    m_pAddCSVBtn = new QPushButton(tr("Add via CSV File"));
    m_pAddCSVBtn->setDefault(true);

    m_pAddTXTBtn = new QPushButton(tr("Add via Text File"));
    m_pAddTXTBtn->setDefault(true);

    m_pTextList = new QListWidget(this);
    m_pTextList->setSelectionMode(QAbstractItemView::MultiSelection);

    QHBoxLayout *pBtnLayout = new QHBoxLayout(this);
    pBtnLayout->addWidget(m_pAddTextBtn);
    pBtnLayout->addWidget(m_pRemoveBtn);
    pBtnLayout->addWidget(m_pClearBtn);
    pBtnLayout->addWidget(m_pAddCSVBtn);
    pBtnLayout->addWidget(m_pAddTXTBtn);

    QVBoxLayout *pSpinLayout = new QVBoxLayout(this);
    pSpinLayout->addLayout(pBtnLayout);
    pSpinLayout->addWidget(m_pSpinEdit);
    pSpinLayout->addWidget(m_pTextList);

    pSpinGroupBox->setLayout(pSpinLayout);

    pMainLayout->addWidget(pTypeGroupBox);
    pMainLayout->addWidget(pSpinGroupBox);
    setLayout(pMainLayout);
}

//private slots:
void CTextTab::onAddTextClicked(){

}

void CTextTab::onRemoveClicked(){

}

void CTextTab::onClearClicked(){

}

void CTextTab::onAddCSVClicked(){

}

void CTextTab::onAddTXTClicked(){

}
