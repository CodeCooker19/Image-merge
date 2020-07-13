#include "COutputTab.h"
#include "../global.h"
#include "CMergeThread.h"

COutputTab::COutputTab(QWidget *parent) : QWidget(parent)
{
    initUI();
    m_pTemplateRadio[0]->setChecked(true);
    connect(m_pOutputBtn, SIGNAL(clicked(bool)), this, SLOT(onOutputClicked()));
    connect(m_pStartMergeBtn, SIGNAL(clicked(bool)), this, SLOT(onMergeClicked()));
}

OUTPUT_INFO COutputTab::getOuputInfo(){
    OUTPUT_INFO info;
    info.m_nCount = m_pImageNumSpin->value();
    info.m_strKeyword = m_pKeywordEdit->text();
    info.m_strOutputPath = m_pOutputEdit->text();
    for(int i=0; i<TEMPLATE_NUM; i++){
        if(m_pTemplateRadio[i]->isChecked()){
            info.m_nTemplate = i;
            break;
        }
    }

    return info;
}

//private:
void COutputTab::initUI(){
    QVBoxLayout *pMainLayout = new QVBoxLayout(this);

   m_pOutputBtn = new QPushButton(tr("Select Output Folder"));
   m_pOutputEdit = new QLineEdit(this);
   m_pOutputEdit->setFixedWidth(g_sizeDLG.width()*0.7);
   m_pOutputEdit->setPlaceholderText(tr("Select output path..."));
   m_pOutputEdit->setReadOnly(true);

   QLabel *pKeywordLabel = new QLabel(tr("Keyword : "));
   m_pKeywordEdit = new QLineEdit(this);
   m_pKeywordEdit->setFixedWidth(g_sizeDLG.width()*0.7);
   m_pKeywordEdit->setPlaceholderText(tr("Input keyword..."));

   QLabel *pOutputLabel = new QLabel(tr("Output images : "));
   m_pImageNumSpin = new QSpinBox(this);
   m_pImageNumSpin->setMinimum(1);
   m_pImageNumSpin->setMaximum(MAX_NUM);
   m_pImageNumSpin->setValue(1);

   m_pStartMergeBtn = new QPushButton(tr("Start Merging..."));

   m_pProgressBar = new QProgressBar(this);
   m_pProgressBar->setRange(0, 100);
   m_pProgressBar->setValue(0);

   QGroupBox *pTemplateGroupBox = new QGroupBox(tr("Merging Type"));
   m_pTemplateLabel = new QLabel(this);

   QPixmap img = QPixmap(":/images/template1.png");
   m_pTemplateLabel->setPixmap(img);
   m_pTemplateLabel->setScaledContents(false);
   m_pTemplateLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

   QHBoxLayout *pPathLayout = new QHBoxLayout(this);
   pPathLayout->addWidget(m_pOutputBtn);
   pPathLayout->addWidget(m_pOutputEdit);

   QHBoxLayout *pKeywordLayout = new QHBoxLayout(this);
   pKeywordLayout->addWidget(pKeywordLabel);
   pKeywordLayout->addWidget(m_pKeywordEdit);

   QHBoxLayout *pNumLayout = new QHBoxLayout(this);
   pNumLayout->addWidget(pOutputLabel);
   pNumLayout->addWidget(m_pImageNumSpin);
   pNumLayout->addStretch();

   QVBoxLayout *pRadioLayout = new QVBoxLayout(this);
   QFont font = this->font();
   font.setPixelSize(FONT_SIZE * 0.7);
   for(int i=0; i<TEMPLATE_NUM; i++){
       m_pTemplateRadio[i] = new QRadioButton(tr("template") + QString::number(i+1));
       m_pTemplateRadio[i]->setFixedWidth(g_sizeDLG.width()/5);
       m_pTemplateRadio[i]->setFont(font);
       pRadioLayout->addWidget(m_pTemplateRadio[i]);
       connect(m_pTemplateRadio[i], SIGNAL(clicked(bool)), this, SLOT(onTemplateClicked()));
   }

   QHBoxLayout *pTemplateLayout = new QHBoxLayout(this);
   pTemplateLayout->addLayout(pRadioLayout);
   pTemplateLayout->addWidget(m_pTemplateLabel, 0, Qt::AlignCenter);

   pTemplateGroupBox->setLayout(pTemplateLayout);

   pMainLayout->addLayout(pPathLayout);
   pMainLayout->addLayout(pKeywordLayout);
   pMainLayout->addLayout(pNumLayout);
   pMainLayout->addWidget(m_pStartMergeBtn);
   pMainLayout->addWidget(m_pProgressBar);
   pMainLayout->addWidget(pTemplateGroupBox);
   setLayout(pMainLayout);
}

//private slots:
void COutputTab::onOutputClicked(){
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        m_pOutputEdit->setText(directory);
    }
}

void COutputTab::onMergeClicked(){
    CMergeThread *pMergeThread = new CMergeThread(this);
    connect(pMergeThread, SIGNAL(processing(int)), this, SLOT(onProcessing(int)));
    connect(pMergeThread, SIGNAL(finished()), this, SLOT(onProcessingFinished()));
    connect(pMergeThread, SIGNAL(finished()), pMergeThread, SLOT(deleteLater()));
    pMergeThread->start();
    m_pProgressBar->setValue(0);
    m_pStartMergeBtn->setEnabled(false);
}

void COutputTab::onTemplateClicked(){
    QObject *object = QObject::sender();
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(object);
    QString name = pbtn->text();

    QPixmap img = QPixmap(":/images/" + name + ".png");
    m_pTemplateLabel->setPixmap(img);
}

void COutputTab::onProcessing(int index){
    int nVal;
    nVal = index * 100 / m_pImageNumSpin->value();
    m_pProgressBar->setValue(nVal);
}

void COutputTab::onProcessingFinished(){
    QMessageBox::information(this, "Info", "Process Successful.");
    m_pStartMergeBtn->setEnabled(true);
    m_pProgressBar->setValue(0);
}
