#ifndef CCUSTOMIZETAB_H
#define CCUSTOMIZETAB_H

#include <QWidget>
#include <QtWidgets>
#include "../global.h"

class CColorImage : public QWidget{
    Q_OBJECT
public:
    explicit CColorImage(QColor color = Qt::black, QWidget *parent = nullptr); 
    void        setColor(QColor color){m_color = color;}
    QColor      getColor(){return m_color;}

private:
    QColor      m_color;

protected:
    void        paintEvent(QPaintEvent *event);
};

class CCustomizeTab : public QWidget
{
    Q_OBJECT
public:
    explicit CCustomizeTab(QWidget *parent = nullptr);
    CUSTOM_INFO getCustomInfo();

private:
    void    initUI();
    void    setupFontTree();

private:
    QTreeWidget     *m_pFontTypeList;
    QSpinBox        *m_pFontSizeSpin;
    CColorImage     *m_pFontColorLabel;
    QPushButton     *m_pFontColorBtn;
    CColorImage     *m_pBackColorLabel;
    QPushButton     *m_pBackColorBtn;
    QTextEdit       *m_pPreviewTextEdit;
    QLabel          *m_pOpacityLabel;
    QSpinBox        *m_pOpacitySpin;
    QSlider         *m_pOpacitySlider;
    QFont           m_font;

signals:

private slots:
    void    showFont(QTreeWidgetItem *item);
    void    updateStyles(QTreeWidgetItem *item, int column);
    void    onFontSizeChange(int);
    void    onFontColorClicked();
    void    onBackColorClicked();
    void    onOpacitySpinChange(int);
    void    onOpacitySliderChange(int);

protected:
    void    showEvent(QShowEvent *event);
};

#endif // CCUSTOMIZETAB_H
