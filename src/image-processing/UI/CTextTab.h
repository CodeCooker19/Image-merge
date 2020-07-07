#ifndef CTEXTTAB_H
#define CTEXTTAB_H

#include <QWidget>
#include <QtWidgets>
#include "../global.h"

class CTextTab : public QWidget
{
    Q_OBJECT
public:
    explicit CTextTab(QWidget *parent = nullptr);
    TEXT_INFO   getTextInfo();

private:
    void        initUI();

private:
    QRadioButton    *m_pAreaRadioBtn;
    QRadioButton    *m_pOverlayRadioBtn;
    QComboBox       *m_pAreaCombo;
    QComboBox       *m_pOverlayCombo;
    QLineEdit       *m_pSpinEdit;
    QPushButton     *m_pAddTextBtn;
    QPushButton     *m_pRemoveBtn;
    QPushButton     *m_pClearBtn;
    QPushButton     *m_pAddCSVBtn;
    QPushButton     *m_pAddTXTBtn;
    QListWidget     *m_pTextList;
signals:

private slots:
    void    onAddTextClicked();
    void    onRemoveClicked();
    void    onClearClicked();
    void    onAddCSVClicked();
    void    onAddTXTClicked();
};

#endif // CTEXTTAB_H
