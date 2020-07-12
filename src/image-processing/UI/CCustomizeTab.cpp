#include "CCustomizeTab.h"
#include "../global.h"

//class CColorImage
//public:
CColorImage::CColorImage(QColor color, QWidget *parent) : QWidget(parent)
{
    m_color = color;
}

//protected:
void CColorImage::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    paint.fillRect(rect(), m_color);
    QWidget::paintEvent(event);
}

//class CCustomizeTab
//public
CCustomizeTab::CCustomizeTab(QWidget *parent) : QWidget(parent)
{
    initUI();
    setupFontTree();
    connect(m_pFontTypeList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(showFont(QTreeWidgetItem*)));
    connect(m_pFontTypeList, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(updateStyles(QTreeWidgetItem*,int)));
    connect(m_pFontSizeSpin, SIGNAL(valueChanged(int)), this, SLOT(onFontSizeChange(int)));
    connect(m_pOpacitySpin, SIGNAL(valueChanged(int)), this, SLOT(onOpacitySpinChange(int)));
    connect(m_pOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(onOpacitySliderChange(int)));
    connect(m_pFontColorBtn, SIGNAL(clicked(bool)), this, SLOT(onFontColorClicked()));
    connect(m_pBackColorBtn, SIGNAL(clicked(bool)), this, SLOT(onBackColorClicked()));
}

CUSTOM_INFO CCustomizeTab::getCustomInfo(){
    CUSTOM_INFO info;
    info.m_colorFont = m_pFontColorLabel->getColor();
    info.m_colorBack = m_pBackColorLabel->getColor();
    info.m_nOpacity = m_pOpacitySlider->value();
    m_font.setPointSize(m_pFontSizeSpin->value());
    info.m_font = m_font;
    return info;
}

//private:
void CCustomizeTab::initUI(){
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);

    QLabel *pFontTypeLabel = new QLabel(tr("Font Type"));
    m_pFontTypeList = new QTreeWidget(this);
    m_pFontTypeList->setFixedWidth(g_sizeDLG.width()/3);

    QLabel *pFontSizeLabel = new QLabel(tr("Font Size : "));
    m_pFontSizeSpin = new QSpinBox(this);
    m_pFontSizeSpin->setMinimum(1);
    m_pFontSizeSpin->setMaximum(100);
    m_pFontSizeSpin->setValue(50);

    QLabel *pFontColorLabel = new QLabel(tr("Font Color : "));
    m_pFontColorLabel = new CColorImage(Qt::black, this);
    m_pFontColorLabel->setFixedSize(g_sizeDLG.height()/25, g_sizeDLG.height()/25);
    m_pFontColorBtn = new QPushButton(tr("Pick Color"));
    m_pFontColorBtn->setDefault(true);

    QLabel *pBackColorLabel = new QLabel(tr("Background Color : "));
    m_pBackColorLabel = new CColorImage(Qt::white, this);
    m_pBackColorLabel->setFixedSize(g_sizeDLG.height()/25, g_sizeDLG.height()/25);
    m_pBackColorBtn = new QPushButton(tr("Pick Color"));
    m_pBackColorBtn->setDefault(true);

    m_pOpacityLabel = new QLabel(STR_OPACITY);
    m_pOpacitySpin = new QSpinBox(this);
    m_pOpacitySpin->setMinimum(0);
    m_pOpacitySpin->setMaximum(100);
    m_pOpacitySpin->setValue(100);

    m_pOpacitySlider = new QSlider(Qt::Horizontal, this);
    m_pOpacitySlider->setMinimum(0);
    m_pOpacitySlider->setMaximum(100);
    m_pOpacitySlider->setValue(100);

    QLabel *pExplainLabel = new QLabel(tr("(Value of alpha property between 0 and 100)"));
    QFont font = this->font();
    font.setPixelSize(FONT_SIZE * 0.7);
    pExplainLabel->setFont(font);

    QLabel *pPreviewLabel = new QLabel(tr("Preview Text"));
    m_pPreviewTextEdit = new QTextEdit(this);

    QVBoxLayout *pTypeLayout = new QVBoxLayout(this);
    pTypeLayout->addWidget(pFontTypeLabel);
    pTypeLayout->addWidget(m_pFontTypeList);

    QHBoxLayout *pSizeLayout = new QHBoxLayout(this);
    pSizeLayout->addWidget(pFontSizeLabel);
    pSizeLayout->addWidget(m_pFontSizeSpin);

    QHBoxLayout *pColorLayout = new QHBoxLayout(this);
    pColorLayout->addWidget(pFontColorLabel);
    pColorLayout->addWidget(m_pFontColorLabel);
    pColorLayout->addWidget(m_pFontColorBtn);

    QHBoxLayout *pBackLayout = new QHBoxLayout(this);
    pBackLayout->addWidget(pBackColorLabel);
    pBackLayout->addWidget(m_pBackColorLabel);
    pBackLayout->addWidget(m_pBackColorBtn);

    QHBoxLayout *pOpacityLayout = new QHBoxLayout(this);
    pOpacityLayout->addWidget(m_pOpacityLabel);
    pOpacityLayout->addWidget(m_pOpacitySpin);

    QVBoxLayout *pVTempLayout = new QVBoxLayout(this);
    pVTempLayout->addLayout(pSizeLayout);
    pVTempLayout->addLayout(pColorLayout);
    pVTempLayout->addLayout(pBackLayout);
    pVTempLayout->addLayout(pOpacityLayout);
    pVTempLayout->addWidget(m_pOpacitySlider);
    pVTempLayout->addWidget(pExplainLabel);

    QVBoxLayout *pPreviewLayout = new QVBoxLayout(this);
    pPreviewLayout->addWidget(pPreviewLabel);
    pPreviewLayout->addWidget(m_pPreviewTextEdit);
    pPreviewLayout->addLayout(pVTempLayout);

    pMainLayout->addLayout(pTypeLayout);
    pMainLayout->addLayout(pPreviewLayout);
    setLayout(pMainLayout);
}

void CCustomizeTab::setupFontTree()
{
    QFontDatabase database;
    m_pFontTypeList->setColumnCount(1);
    m_pFontTypeList->setHeaderLabels(QStringList() << tr("Font"));

    foreach (QString family, database.families()) {
        const QStringList styles = database.styles(family);
        if (styles.isEmpty())
            continue;

        QTreeWidgetItem *familyItem = new QTreeWidgetItem(m_pFontTypeList);
        familyItem->setText(0, family);
        familyItem->setCheckState(0, Qt::Unchecked);
        familyItem->setFlags(familyItem->flags() | Qt::ItemIsAutoTristate);

        foreach (QString style, styles) {
            QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);
            styleItem->setCheckState(0, Qt::Unchecked);
            styleItem->setData(0, Qt::UserRole, QVariant(database.weight(family, style)));
            styleItem->setData(0, Qt::UserRole + 1, QVariant(database.italic(family, style)));
        }
    }
}

//private slots:
void CCustomizeTab::showFont(QTreeWidgetItem *item)
{
    if (!item)
        return;

    QString family;
    QString style;
    int weight;
    bool italic;
    int nFontSize;

    if (item->parent()) {
        family = item->parent()->text(0);
        style = item->text(0);
        weight = item->data(0, Qt::UserRole).toInt();
        italic = item->data(0, Qt::UserRole + 1).toBool();
    } else {
        family = item->text(0);
        style = item->child(0)->text(0);
        weight = item->child(0)->data(0, Qt::UserRole).toInt();
        italic = item->child(0)->data(0, Qt::UserRole + 1).toBool();
    }

    nFontSize = m_pFontSizeSpin->value();

    QString oldText = m_pPreviewTextEdit->toPlainText().trimmed();
    bool modified = m_pPreviewTextEdit->document()->isModified();
    m_pPreviewTextEdit->clear();
    QFont font(family, nFontSize, weight, italic);
    font.setStyleName(style);
    m_pPreviewTextEdit->document()->setDefaultFont(font);

    QTextCursor cursor = m_pPreviewTextEdit->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(blockFormat);

    if (modified)
        cursor.insertText(QString(oldText));
    else
        cursor.insertText(QString("%1 %2").arg(family).arg(style));

    m_pPreviewTextEdit->document()->setModified(modified);
    m_font = font;
}

void CCustomizeTab::updateStyles(QTreeWidgetItem *item, int column)
{
    if (!item || column != 0)
        return;
}

void CCustomizeTab::onFontSizeChange(int nFontSize){
    QString oldText = m_pPreviewTextEdit->toPlainText().trimmed();
    bool modified = m_pPreviewTextEdit->document()->isModified();
    m_pPreviewTextEdit->clear();
    QFont font = m_pPreviewTextEdit->document()->defaultFont();

    font.setPointSize(nFontSize);
    m_pPreviewTextEdit->document()->setDefaultFont(font);

    QTextCursor cursor = m_pPreviewTextEdit->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(blockFormat);

    cursor.insertText(QString(oldText));
    m_pPreviewTextEdit->document()->setModified(modified);
    m_font = font;
}

void CCustomizeTab::onFontColorClicked(){
    QColor color = m_pFontColorLabel->getColor();
    color = QColorDialog::getColor(color);
    m_pFontColorLabel->setColor(color);

    QString oldText = m_pPreviewTextEdit->toPlainText().trimmed();
    bool modified = m_pPreviewTextEdit->document()->isModified();
    m_pPreviewTextEdit->clear();
    m_pPreviewTextEdit->setTextColor(color);

    QTextCursor cursor = m_pPreviewTextEdit->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(blockFormat);

    cursor.insertText(QString(oldText));
    m_pPreviewTextEdit->document()->setModified(modified);
}

void CCustomizeTab::onBackColorClicked(){
    QColor color = m_pBackColorLabel->getColor();
    color = QColorDialog::getColor(color);
    m_pBackColorLabel->setColor(color);

    QString oldText = m_pPreviewTextEdit->toPlainText().trimmed();
    bool modified = m_pPreviewTextEdit->document()->isModified();
    m_pPreviewTextEdit->clear();
    m_pPreviewTextEdit->setTextBackgroundColor(color);

    QTextCursor cursor = m_pPreviewTextEdit->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(blockFormat);

    cursor.insertText(QString(oldText));
    m_pPreviewTextEdit->document()->setModified(modified);
}

void CCustomizeTab::onOpacitySpinChange(int nOpacity){
    m_pOpacitySlider->setValue(nOpacity);
}

void CCustomizeTab::onOpacitySliderChange(int nOpacity){
    m_pOpacitySpin->setValue(nOpacity);
}

//protected:
void CCustomizeTab::showEvent(QShowEvent *event){
    showFont(m_pFontTypeList->topLevelItem(0));
    QWidget::showEvent(event);
}
