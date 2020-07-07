#ifndef COUTPUTTAB_H
#define COUTPUTTAB_H

#include <QWidget>
#include <QtWidgets>
#include "../global.h"

class COutputTab : public QWidget
{
    Q_OBJECT
public:
    explicit COutputTab(QWidget *parent = nullptr);
    OUTPUT_INFO    getOuputInfo();

private:
    void    initUI();

private:
    QPushButton     *m_pOutputBtn;
    QLineEdit       *m_pOutputEdit;
    QLineEdit       *m_pKeywordEdit;
    QSpinBox        *m_pImageNumSpin;
    QPushButton     *m_pStartMergeBtn;
    QProgressBar    *m_pProgressBar;
    QRadioButton    *m_pTemplateRadio[TEMPLATE_NUM];
    QLabel          *m_pTemplateLabel;

signals:

private slots:
    void    onOutputClicked();
    void    onMergeClicked();
    void    onTemplateClicked();
    void    onProcessing(int index);
    void    onProcessingFinished();
};

#endif // COUTPUTTAB_H
